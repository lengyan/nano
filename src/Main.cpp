/*
 * Title: 主函数
 * Description: 主函数
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-02
 *     Email: zhust2003@gmail.com 
 */

#include "World.h"
#include "ByteBuffer.h"
#include "utils/Config.h"
#include "ace/CDR_Stream.h"
#include "ace/Basic_Types.h"
#include "WorldTask.h"
#include "utils/Logger.h"
#include <vector>

/**
 * @brief   ACE_TMAIN 
 *
 * @param   argc
 * @param   argv
 *
 * @return  
 */
int ACE_TMAIN(int argc, ACE_TCHAR **argv) {    

    gConfig->open("nano.ini");
    
    // 启动世界进程
    WorldTask wt;
    wt.activate();
    
    gWorld->init();
//    gWorld->run();
	return 0;
}
