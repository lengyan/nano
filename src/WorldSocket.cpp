/**
 * @file WorldSocket.cpp
 * @brief  世界Socket管理
 * @author Dalton
 * @version 0.1
 * @date 2011-01-08
 */

#include "WorldSocket.h"
#include <fstream>
#include <string>
#include <iostream>
#include "ace/Basic_Types.h"
#include "Opcodes.h"
#include "utils/Logger.h"

/**
 * @brief   WorldSocket 构造函数
 *
 */
WorldSocket::WorldSocket():headerBuffer(sizeof(ClientPktHeader)),
                           bodyBuffer(),
                           packet(0),
                           session(0),
                           isClose(false)
{

}

WorldSocket::~WorldSocket() {
    // 这个不知道什么时候调用
    delete packet;
    delete session;
}

/**
 * @brief   open 打开socket
 *
 * @param   p
 *
 * @return  
 */
int WorldSocket::open(void *p) {
    // 不知到干啥的
	if (super::open(p) == -1)
		return -1;

	ACE_TCHAR peer_name[MAXHOSTNAMELEN];
	ACE_INET_Addr peer_addr;
	if (this->peer().get_remote_addr(peer_addr) == 0 &&
		peer_addr.addr_to_string(peer_name, MAXHOSTNAMELEN) == 0)
		ACE_DEBUG((LM_DEBUG,
					ACE_TEXT("(%P|%t)%T Connection from %s\n"),
					peer_name));

	return 0;
}

/**
 * @brief   handle_input 处理输入
 *
 * @param   ACE_HANDLE
 *
 * @return  -1代表此次处理出错,将调用handleclose,
 *          0代表继续检测事件,
 *          >0代表调用检测事件(需小心,除非你真有把握没读取完),并继续检测
 */
int WorldSocket::handle_input(ACE_HANDLE) {
	const size_t INPUT_SIZE = 4096;
	char buffer[INPUT_SIZE];

    // 接收数据数
	ssize_t recv_cnt, send_cnt;
    
    // 读取的信息放在message_block里
	ACE_Message_Block readBuffer(4096);

    // 接受至缓冲区 
	recv_cnt = this->peer().recv(readBuffer.wr_ptr(), readBuffer.space());

    // 如果是多线程，这样也不靠谱
	if (recv_cnt <= 0) {
		ACE_DEBUG((LM_DEBUG,
					ACE_TEXT("(%P|%t)%T Connection closed\n")));
		return -1;
	}

    // 移动下写指针
    readBuffer.wr_ptr(recv_cnt);

    // 打印接受的信息
    ACE_HEX_DUMP((LM_DEBUG, readBuffer.rd_ptr(), recv_cnt, "recv:"));

    // 请求策略文件字符串
    std::string flashRequest = "<policy-file-request/>";

    // 如果是策略文件请求
    if (flashRequest.compare(readBuffer.rd_ptr()) == 0) {
        gLogger->info("send crossdomain\n");
        // send crossdomain
        std::ifstream ifs("crossdomain.xml");
        std::string content((std::istreambuf_iterator<char>(ifs)), 
                            (std::istreambuf_iterator<char>()));
        this->peer().send(content.c_str(), content.length() + 1);
        return 0;
    }

    // 将抓到的content处理下
    while (readBuffer.length() > 0) {
        // 如果包头有空余
        if (headerBuffer.space() > 0) {
            // 最多只取头部那么大
            const size_t copySize = (readBuffer.length() > headerBuffer.space() ? headerBuffer.space() : readBuffer.length());
            headerBuffer.copy(readBuffer.rd_ptr(), copySize);
            // 移动指针
            readBuffer.rd_ptr(copySize);

            // 如果还是没接收完头部,重新接收
            if (headerBuffer.space() > 0) {
                // 应该不可能还没有读完缓存
                ACE_ASSERT(readBuffer.length() == 0);
                // 当前资源不可用,等下再读
                errno = EWOULDBLOCK;
                return 0;
            }
            if (handle_input_header() == -1) {
                return -1;
            }
        }

        // 如果包体有空余
        if (bodyBuffer.space() > 0) {
            // 最多只取头部那么大
            const size_t copySize = (readBuffer.length() > bodyBuffer.space() ? bodyBuffer.space() : readBuffer.length());
            bodyBuffer.copy(readBuffer.rd_ptr(), copySize);
            // 移动指针
            readBuffer.rd_ptr(copySize);

            // 如果还是没接收完头部,重新接收
            if (bodyBuffer.space() > 0) {
                // 应该不可能还没有读完缓存
                ACE_ASSERT(readBuffer.length() == 0);
                // 当前资源不可用,等下再读
                errno = EWOULDBLOCK;
                return 0;
            }

            handle_input_body();
        }
    }

	return 0;
}

/**
 * @brief   sendPacket 发送服务端包
 *
 * @param   buffer
 *
 * @return  
 */
int WorldSocket::sendPacket(ACE_Message_Block &buffer) {
    ssize_t sendCnt,
            bufferCnt = ACE_static_cast(size_t, buffer.length());
    // FIXME 发送给一个已经关闭的peer,会出错的
	sendCnt = this->peer().send(buffer.rd_ptr(), bufferCnt);
    // send
    // ACE_HEX_DUMP((LM_DEBUG, buffer.rd_ptr(), buffer.length(), "send:"));
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%i\n"), sendCnt)); 
	if (sendCnt == bufferCnt)
		return 0;
	if (sendCnt == -1 && ACE_OS::last_error() != EWOULDBLOCK)
		ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("%P|%t) %p\n"),
						ACE_TEXT("send")),
						-1);
	if (sendCnt == -1)
		sendCnt = 0;
    // 移动指针
    buffer.rd_ptr(sendCnt);
	ACE_Message_Block *mb;
	size_t remaining = ACE_static_cast(size_t, (bufferCnt - sendCnt));
	ACE_NEW_RETURN(mb, ACE_Message_Block(buffer.rd_ptr(), remaining), -1);
	int output_off = this->msg_queue()->is_empty();
	ACE_Time_Value nowait(ACE_OS::gettimeofday());
	if (this->putq(mb, &nowait) == -1) {
		ACE_ERROR((LM_ERROR,
					ACE_TEXT("(%P|%t) %p; discarding data\n"),
					ACE_TEXT("enqueue failed")));
		mb->release();
		return 0;
	}
	if (output_off)
		return this->reactor()->register_handler(this, ACE_Event_Handler::WRITE_MASK);
}

/**
 * @brief   handle_output 处理输出,reator输出事件回调函数
 *
 * @param   ACE_HANDLE
 *
 * @return  
 */
int WorldSocket::handle_output(ACE_HANDLE) {
	ACE_Message_Block *mb;
	ACE_Time_Value nowait(ACE_OS::gettimeofday());
	while (-1 != this->getq(mb, &nowait)) {
		ssize_t send_cnt = this->peer().send(mb->rd_ptr(), mb->length());
		if (send_cnt == -1)
			ACE_ERROR((LM_ERROR,
						ACE_TEXT("(%P|%t) %p\n"),
						ACE_TEXT("send")));
		else
			mb->rd_ptr(ACE_static_cast(size_t, send_cnt));
		if (mb->length() > 0) {
			this->ungetq(mb);
			break;
		}
		mb->release();
	}
	return (this->msg_queue()->is_empty()) ? -1 : 0;
}

/**
 * @brief   handle_input_header 处理接收到的头部
 *
 * @return  
 */
int WorldSocket::handle_input_header(void) {
    ClientPktHeader* header = (ClientPktHeader*) headerBuffer.rd_ptr();
    // 网络字节序->小端字节序
    // intel为小端
    header->size = ntohs(header->size);
    header->cmd = ntohs(header->cmd);

    // 判断异常头格式
    if (header->size <= 0) {
        ACE_ERROR((LM_ERROR, ACE_TEXT("header packet error: header size %i, header cmd %i\n"), header->size, header->cmd));
        errno = EINVAL;
        return -1;
    }
    // 打印头部的信息
    gLogger->hexDump(LM_DEBUG, headerBuffer.rd_ptr(), headerBuffer.length(), "header:");
    gLogger->debug("header size %i, header cmd %i\n", header->size, header->cmd);
    
    // 初始化世界包
    ACE_NEW_RETURN(packet, WorldPacket(header->cmd, header->size), -1);

    // 分配空间
    packet->resize(header->size);
    
    // 重新初始化bodyBuffer
    bodyBuffer.init((char*) packet->contents(),packet->size());
}

/**
 * @brief   handle_input_body 处理包体信息
 *
 * @return  
 */
int WorldSocket::handle_input_body(void) {
    // 断言包头及包体应该都接收满
    ACE_ASSERT(headerBuffer.space() == 0);
    ACE_ASSERT(bodyBuffer.space() == 0);
    
    // 打印头部的信息
    gLogger->hexDump(LM_DEBUG, (char*)packet->contents(), packet->size(), "body:");
    processMessage();

    // 重置缓存
    headerBuffer.reset();
    bodyBuffer.reset();
    // 空指针,好习惯
    packet = NULL;

    return 0;
}

/**
 * @brief   processMessage 处理消息
 *
 * @return  
 */
int WorldSocket::processMessage() {
    // 因为这里是队列的方式,无法用智能指针删除.
    // 所以这里删除的同时,在sessionUpdate也需要删除.
    ACE_Auto_Ptr<WorldPacket> aptr(packet);
    uint16 opcode = packet->getOpcode();
    uint32 id = 1;
    // 插入处理队列,多线程处理游戏逻辑,不在这里处理,否则会阻塞
    // FIXME 异常处理
    switch (opcode) {
        // 用户认证协议
        case CMSG_AUTH_SESSION:
            // TODO 一堆验证逻辑
            // 生成会话对象
            // 虽然在这里new,但不在这里delete,在worldupdate循环中删除
            ACE_NEW_RETURN(session, WorldSession(id, this), -1);
            // 给世界增加会话
            gWorld->addSession(session);
            break;
        default:
            // 这里不给智能指针进行清理
            // 交给session update处理
            aptr.release ();
            session->pushMessage(packet);
            break;
    }
    return 0;
}

/**
 * @brief   handle_close 处理关闭
 *
 * @param   h
 * @param   mask
 *
 * @return  
 */
int WorldSocket::handle_close(ACE_HANDLE h, ACE_Reactor_Mask mask) {
	if (mask == ACE_Event_Handler::WRITE_MASK)
		return 0;
    // 退出
    // 设定关闭标志位
    // 设定session为空指针
    // delete放置在world中
    gLogger->debug("some one close\n");
    isClose = true;
    session = NULL;
	return super::handle_close(h, mask);
}

/**
 * @brief   isClose 返回客户端是否已关闭
 *
 * @return  
 */
bool WorldSocket::isClosed() {
    return isClose;
}
