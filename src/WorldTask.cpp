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
 
#include "WorldTask.h"
#include "World.h"
#include "utils/Logger.h"

#define WORLD_SLEEP_CONST 50
/**
 * 世界运行线程
 * */
int WorldTask::svc(void) {
    while(1) {
        gWorld->update();
        ACE_OS::sleep(ACE_Time_Value(0, 1000 * WORLD_SLEEP_CONST));
    }
}
