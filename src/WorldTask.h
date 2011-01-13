/*
 * Title: 世界心跳任务
 * Description: 世界心跳任务
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-03
 *     Email: zhust2003@gmail.com 
 */

#ifndef _WORLDTASK_H
#define _WORLDTASK_H

#include "ace/Task.h"

class WorldTask : public ACE_Task_Base
{
    public:
        virtual int svc(void);
};

#endif
