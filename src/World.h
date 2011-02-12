/**
 * @file World.h
 * @brief   世界类
 * @author Dalton
 * @version 0.1
 * @date 2011-01-13
 */
#ifndef _WORLD_H
#define _WORLD_H

#include "WorldSession.h"
#include "ace/Singleton.h"
#include <map>


class World 
{
    // ace singleton
    friend class ACE_Singleton<World, ACE_Recursive_Thread_Mutex>;
    public:
        World();
        ~World();

        // 初始化
        int init();
        void run();
        void update();

        // 维护会话
        void addSession(WorldSession* s);
        void removeSession(uint32 id);
        WorldSession* findSession(uint32 id) const;
        void sendGlobalMessage(WorldPacket* worldPacket);
    private:
        typedef std::map<uint32, WorldSession*> SessionMap;
        SessionMap sessionMap;
};

#define gWorld ACE_Singleton<World, ACE_Recursive_Thread_Mutex>::instance()

#endif
