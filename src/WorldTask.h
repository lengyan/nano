#ifndef _WORLDTASK_H
#define _WORLDTASK_H

#include "ace/Task.h"
// world task
// 世界心跳更新
// 主要流程,迭代会话,执行会话更新
// ok
class WorldTask : public ACE_Task_Base
{
    public:
        int svc(void);
};

#endif
