/*
 * Title: 世界Socket管理
 * Description: 世界Socket管理
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-03
 *     Email: zhust2003@gmail.com 
 */

#ifndef _WORLDSOCKET_H
#define _WORLDSOCKET_H

#include "ace/Message_Block.h"
#include "ace/SOCK_Stream.h"
#include "ace/Svc_Handler.h"
#include "ace/OS.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Acceptor.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"

// 服务端包头格式
struct ServerPktHeader {
    uint16 size;
    uint16 cmd;
};
// 客户端包头格式
struct ClientPktHeader {
    uint16 size;
    uint16 cmd;
};



class WorldSocket : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> {
public:
    WorldSocket();
    ~WorldSocket();
    typedef ACE_Acceptor<WorldSocket, ACE_SOCK_ACCEPTOR> Acceptor;
	int open(void * = 0);
	virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
	virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
    int handle_input_header(void);
    int handle_input_body(void);
    int processMessage();
    int sendPacket(ACE_Message_Block &buffer);
    bool isClosed();
private:
    typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super;
    // 消息头缓冲区
    ACE_Message_Block headerBuffer;
    // 消息体缓冲区
    ACE_Message_Block bodyBuffer;
    // 包里的消息
    WorldPacket* packet;
    // 世界会话
    WorldSession* session;
    // 是否已经关闭会话
    bool isClose;
};


#endif
