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

#ifndef _WORLDSESSION_H
#define _WORLDSESSION_H

#include <deque>
#include "Define.h"
#include "utils/Logger.h"
#include "WorldPacket.h"
#include "LockedQueue.h"

// 防止类相互嵌套
class WorldSocket;

/*
 * =====================================================================================
 *        Class:  WorldSession
 *  Description:  用户会话
 * =====================================================================================
 */
class WorldSession
{
    public:
        WorldSession(uint32 id, WorldSocket* worldSocket);
        WorldSession(uint32 id);
        ~WorldSession();
        void update();
        void pushMessage(WorldPacket*);
        void echo();
    private:
        uint32 id;
        WorldSocket* worldSocket;
// 消息队列
// 双端队列
// 注意多线程问题
        LockedQueue<WorldPacket*, ACE_Thread_Mutex> messageQueue;
};


#endif
