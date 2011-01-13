/*
 * Title: 日志处理类
 * Description: 日志处理类
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-02
 *     Email: zhust2003@gmail.com 
 */
#include "Logger.h"

Logger::Logger(){}
Logger::~Logger(){}

void Logger::log(ACE_Log_Priority priority, const ACE_TCHAR* format, ...) {
    va_list vl;
    va_start(vl, format);
    std::string newFormat = std::string(format);
    newFormat = "[" + GetTimestampStr() + "] " + newFormat;
    ACE_DEBUG((newFormat.c_str(), priority, vl));
    va_end(vl);
}

void Logger::debug(const ACE_TCHAR* format, ...) {
    va_list vl;
    va_start(vl, format);
    ACE_DEBUG((format, LM_DEBUG, vl));
    va_end(vl);
}

void Logger::info(const ACE_TCHAR* format, ...) {
    va_list vl;
    va_start(vl, format);
    ACE_DEBUG((format, LM_INFO, vl));
    va_end(vl);
}

void Logger::hexDump(ACE_Log_Priority priority, const char* buffer, size_t size, const ACE_TCHAR* text) {
    ACE_HEX_DUMP((priority, buffer, size, text));
}

std::string Logger::GetTimestampStr()
{
    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    //       YYYY   year
    //       MM     month (2 digits 01-12)
    //       DD     day (2 digits 01-31)
    //       HH     hour (2 digits 00-23)
    //       MM     minutes (2 digits 00-59)
    //       SS     seconds (2 digits 00-59)
    char buf[20];
    snprintf(buf, 
             20, 
             "%04d-%02d-%02d %02d:%02d:%02d", 
             aTm->tm_year + 1900,
             aTm->tm_mon + 1,
             aTm->tm_mday,
             aTm->tm_hour,
             aTm->tm_min,
             aTm->tm_sec);
    return std::string(buf);
}

