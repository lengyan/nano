/**
 * @file Opcodes.h
 * @brief   操作符
 * @author Dalton
 * @version 0.1
 * @date 2011-01-08
 */
#ifndef _OPCODES_H
#define _OPCODES_H

/**
 * 命令标示
 * 命名规则
 * CMSG 客户端发送命令
 * SMSG 服务端发送命令
 * */
enum Opcodes
{
    CMSG_TEST                           = 0x0000,
    CMSG_AUTH_SESSION                   = 0x0010,
    NUM_MSG_TYPES                       = 0x00FF
};


struct OpcodeHandler
{
    char const* name;
    void (WorldSession::*handler)(WorldPacket& recvPacket);
};

#endif
