/*
 * Title: 世界会话
 * Description: 世界会话
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-03
 *     Email: zhust2003@gmail.com 
 */

#include "WorldSession.h"
#include "Opcodes.h"
#include "WorldSocket.h"

/**
 * @brief   WorldSession
 *
 * @param   id
 * @param   id
 */
WorldSession::WorldSession(uint32 id, WorldSocket* worldSocket):id(id),
                                                                worldSocket(worldSocket)
{
}
WorldSession::WorldSession(uint32 id):id(id) {


}
/**
 * @brief   ~WorldSession 
 */
WorldSession::~WorldSession() {
    // 这里的消息队列需要清理
    WorldPacket* packet;
    while(messageQueue.next(packet))
        delete packet;
}

/**
 * @brief   handleNull 非法包
 *
 * @param   packet
 */
void WorldSession::handleNull(WorldPacket& packet) {

}
/**
 * @brief   getUserId 获取用户ID
 */
uint32 WorldSession::getUserId() {
    return id;
}
/**
 * @brief   update
 * 会话更新
 * @return bool false 代表这个会话已经无效,需要清理了
 */
bool WorldSession::update() {
    WorldPacket* packet;

    // 如果客户端已经关闭了,则通知世界删除他
    if (worldSocket->isClosed()) {
        return false;
    }

    // 处理消息队列
    // NEXT每次获取锁,并弹出消息,从队列中删除消息
    // FIXME 异常处理
    while (messageQueue.next(packet)) {
        // 离开作用域后删除指针指向内存
        ACE_Auto_Ptr<WorldPacket> aptr(packet);
        OpcodeHandler const& opHandle = opcodeTable[packet->getOpcode()];
        (this->*opHandle.handler)(*packet);
    }
    return true;
}

/**
 * @brief   pushMessage
 * 加入消息队列
 * @param   packet
 */
void WorldSession::pushMessage(WorldPacket* packet) {
    //gLogger->debug("add packet %d\n", packet->getOpcode());
    messageQueue.add(packet);    
}

void WorldSession::echo() {
    gLogger->debug("echo %d\n", id);
}
