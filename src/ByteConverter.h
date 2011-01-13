/*
 * Title: 字节序转换
 * Description: 字节序转换
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011:01:01
 *     Email: zhust2003@gmail.com 
 */

#ifndef _BYTECONVERTER_H
#define _BYTECONVERTER_H

#include "ace/Basic_Types.h"

namespace ByteConverter
{
    template<size_t T>
        inline void convert(char *val)
    {
        std::swap(*val, *(val + T - 1));
        convert<T - 2>(val + 1);
    }

    template<> inline void convert<0>(char *) {}
    template<> inline void convert<1>(char *) {}            // ignore central byte

    template<typename T> inline void apply(T *val)
    {
        convert<sizeof(T)>((char *)(val));
    }
}

#if defined (ACE_BIG_ENDIAN)
template<typename T> inline void EndianConvert(T& val) { ByteConverter::apply<T>(&val); }
template<typename T> inline void EndianConvertReverse(T&) { }
#else
template<typename T> inline void EndianConvert(T&) { }
template<typename T> inline void EndianConvertReverse(T& val) { ByteConverter::apply<T>(&val); }
#endif

template<typename T> void EndianConvert(T*);         // will generate link error
template<typename T> void EndianConvertReverse(T*);  // will generate link error

inline void EndianConvert(uint8&) { }
inline void EndianConvert( int8&) { }
inline void EndianConvertReverse(uint8&) { }
inline void EndianConvertReverse( int8&) { }

#endif
