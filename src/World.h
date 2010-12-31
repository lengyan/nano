#ifndef _WORLD_H
#define _WORLD_H

#include "WorldSession.h"
#include "ace/Basic_Types.h"
#include "ace/Singleton.h"
#include <vector>

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
        bool removeSession(ACE_UINT32 id);
    private:
        std::vector<WorldSession*> sessionList;
};

#define sWorld ACE_Singleton<World, ACE_Recursive_Thread_Mutex>::instance()

#endif
