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
    CMSG_TEST                           = 0x0001
};

#endif
