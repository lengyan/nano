#include "WorldSocket.h"
#include <fstream>
#include <string>
#include <iostream>
#include "ace/Basic_Types.h"
#include "Opcodes.h"



// 构造函数
WorldSocket::WorldSocket():headerBuffer(sizeof(ClientPktHeader)),
                           bodyBuffer(0),                        
                           header(0)
{

}

WorldSocket::~WorldSocket() {
    if (bodyBuffer)
        delete bodyBuffer;
    
}

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
        std::cout << "send crossdomain" << std::endl;
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
                return -1;
            }
            if (handle_input_header() == -1) {
                return -1;
            }
        }

        // 如果包体有空余
        if (bodyBuffer->space() > 0) {
            // 最多只取头部那么大
            const size_t copySize = (readBuffer.length() > bodyBuffer->space() ? bodyBuffer->space() : readBuffer.length());
            bodyBuffer->copy(readBuffer.rd_ptr(), copySize);
            // 移动指针
            readBuffer.rd_ptr(copySize);

            // 如果还是没接收完头部,重新接收
            if (bodyBuffer->space() > 0) {
                // 应该不可能还没有读完缓存
                ACE_ASSERT(readBuffer.length() == 0);
                // 当前资源不可用,等下再读
                errno = EWOULDBLOCK;
                return -1;
            }

            handle_input_body();
        }

        // 对返回值不是特别理解
        return 0;
    }

    /*
	send_cnt = this->peer().send(buffer, ACE_static_cast(size_t, recv_cnt));
	if (send_cnt == recv_cnt)
		return 0;
	if (send_cnt == -1 && ACE_OS::last_error() != EWOULDBLOCK)
		ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("%P|%t) %p\n"),
						ACE_TEXT("send")),
						0);
	if (send_cnt == -1)
		send_cnt = 0;
	ACE_Message_Block *mb;
	size_t remaining = ACE_static_cast(size_t, (recv_cnt - send_cnt));
	ACE_NEW_RETURN(mb, ACE_Message_Block(&buffer[send_cnt], remaining), -1);
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
    */
	return 0;
}

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

// 处理接收到的头部
int WorldSocket::handle_input_header(void) {
    header = (ClientPktHeader *) headerBuffer.rd_ptr();
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
    ACE_HEX_DUMP((LM_DEBUG, headerBuffer.rd_ptr(), headerBuffer.length(), "header:"));
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("header size %i, header cmd %i\n"), header->size, header->cmd));
    // 初始化bodyBuffer大小
    bodyBuffer = new ACE_Message_Block(header->size);
}

/**
 * 处理包体信息
 *
 * @return int
 * */
int WorldSocket::handle_input_body(void) {
    // 断言包头及包体应该都接收满
    ACE_ASSERT(headerBuffer.space() == 0);
    ACE_ASSERT(bodyBuffer->space() == 0);
    // 打印头部的信息
    ACE_HEX_DUMP((LM_DEBUG, bodyBuffer->rd_ptr(), bodyBuffer->length(), "body:"));
    processMessage();

    // 重置缓存
    headerBuffer.reset();
    bodyBuffer->reset();

    return 0;
}

/**
 * 处理消息
 * */
int WorldSocket::processMessage() {
    ACE_UINT16 opcode = header->cmd;
    switch (opcode) {
        case CMSG_TEST:
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("test")));
            break;
    }
    return 0;
}

// 处理关闭
int WorldSocket::handle_close(ACE_HANDLE h, ACE_Reactor_Mask mask) {
	if (mask == ACE_Event_Handler::WRITE_MASK)
		return 0;
	return super::handle_close(h, mask);
}
