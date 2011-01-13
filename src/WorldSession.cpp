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

/**
 * @brief   WorldSession
 *
 * @param   id
 * @param   id
 */
WorldSession::WorldSession(uint32 id, WorldSocket* worldSocket):id(id),
                                                                worldSocket(worldSocket)
{
    gLogger->debug("init %d\n", id);
}
/**
 * @brief   ~WorldSession 
 */
WorldSession::~WorldSession() {
    gLogger->debug("destory %d\n", id);
}
/**
 * @brief   update
 * 会话更新
 */
void WorldSession::update() {
    WorldPacket* packet;
    // 处理消息队列
    while (messageQueue.next(packet)) {
        packet->getOpcode();
    }

    // 为什么要delete呢
    delete packet;
    //echo();
}

/**
 * @brief   pushMessage
 * 加入消息队列
 * @param   packet
 */
void WorldSession::pushMessage(WorldPacket* packet) {
    messageQueue.add(packet);    
}

void WorldSession::echo() {
    gLogger->debug("echo %d\n", id);
}
