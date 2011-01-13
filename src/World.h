#ifndef _WORLD_H
#define _WORLD_H

#include "WorldSession.h"
#include "ace/Singleton.h"
#include <deque>

// 世界,用来管理所有的游戏会话

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
        bool removeSession(uint32 id);
    private:
        LockedQueue<WorldSession*, ACE_Thread_Mutex> sessionDeque;
};

#define gWorld ACE_Singleton<World, ACE_Recursive_Thread_Mutex>::instance()

#endif
