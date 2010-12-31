#ifndef _WORLDSESSION_H
#define _WORLDSESSION_H
#include <deque>
#include "WorldSocket.h"
// 用户会话

class WorldSession
{
    public:
        WorldSession(ACE_UINT32, WorldSocket);
        WorldSession(ACE_UINT32);
        ~WorldSession();
        void update();
        void pushMessage();
        void echo();
    private:
        ACE_UINT32 id;
// 消息队列
// 直接用std标准容器吧
// 双端队列
        //deque<WorldPacket> _messageQueue;
};


#endif
