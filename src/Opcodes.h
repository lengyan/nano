/**
 * @file Opcodes.h
 * @brief   操作符
 * @author Dalton
 * @version 0.1
 * @date 2011-01-08
 */
#ifndef _OPCODES_H
#define _OPCODES_H

#include "WorldSession.h"
/**
 * 命令标示
 * 命名规则
 * CMSG 客户端发送命令
 * SMSG 服务端发送命令
 * */
enum Opcodes
{
    /** 
     * 认证*/
    CMSG_AUTH_SESSION                   = 0x0000,
    /** 
     * 聊天相关*/
    CMSG_CHAT_SAY                       = 0x0001,
    SMSG_CHAT_SAY                       = 0x0002,
    CMSG_CHAT_WHISPER                   = 0x0003,
    SMSG_CHAT_WHISPER                   = 0x0004,
    CMSG_CHAT_CHANNEL                   = 0x0005,
    SMSG_CHAT_CHANNEL                   = 0x0006,
    CMSG_CHAT_CHANNEL_JOIN              = 0x0007,
    SMSG_CHAT_CHANNEL_JOIN              = 0x0008,
    CMSG_CHAT_CHANNEL_LEAVE             = 0x0009,
    SMSG_CHAT_CHANNEL_LEAVE             = 0x000A,
    CMSG_CHAT_CHANNEL_LIST              = 0x000B,
    SMSG_CHAT_CHANNEL_LIST              = 0x000C,
    /** 
     * for message count*/
    NUM_MSG_TYPES                       = 0x00FF
};


struct OpcodeHandler
{
    char const* name;
    void (WorldSession::*handler)(WorldPacket& recvPacket);
};

extern OpcodeHandler opcodeTable[NUM_MSG_TYPES]; 

#endif
