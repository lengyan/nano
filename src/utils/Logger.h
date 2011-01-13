/*
 * Title: 日志处理类
 * Description: 日志处理类, 不喜欢ace的宏,重新封装了层
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-02
 *     Email: zhust2003@gmail.com 
 * 
 * TODO
 * - 优先级重新设置
 * - 加入颜色支持,针对不同优先级显示不同颜色,查看芒果代码
 * - 定制日志输出转向
 *
 * Thinking
 * Q:debug与trace方法可以直接调用log方法吗
 * A:网上说,只能写汇编(WTF)
 * Q:多线程日志如何处理
 */
 
#ifndef _LOGGER_H
#define _LOGGER_H

#include "ace/Singleton.h"
#include <time.h>
#include <iostream>

class Logger
{
    friend class ACE_Singleton<Logger, ACE_Recursive_Thread_Mutex>;
    public:
        Logger();
        virtual ~Logger();
        void log(ACE_Log_Priority priority, const ACE_TCHAR* format, ...);
        void debug(const ACE_TCHAR* format, ...);
        void info(const ACE_TCHAR* format, ...);
        void hexDump(ACE_Log_Priority priority, const char* buffer, size_t size, const ACE_TCHAR* text = 0);
        std::string GetTimestampStr();
    private:
        
};

#define gLogger ACE_Singleton<Logger, ACE_Recursive_Thread_Mutex>::instance()

#endif /* _LOGGER_H */
