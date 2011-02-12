/*
 * Title: 世界包
 * Description: 基于ByteBuffer的世界包类
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-02
 *     Email: zhust2003@gmail.com 
 */
 
#ifndef _WORLDPACKET_H
#define _WORLDPACKET_H

#include "ByteBuffer.h"


class WorldPacket : public ByteBuffer
{
    public:
        WorldPacket() : ByteBuffer(0), _opcode(0)
        {
        }
        // 禁止隐式转换
        explicit WorldPacket(uint16 opcode, size_t res = 200) : _opcode(opcode), ByteBuffer(res)
        {
        }
        
        uint16 getOpcode() const {
            return _opcode;
        }
        void setOpcode(uint16 opcode) {
            _opcode = opcode;
        }

    private:
        uint16 _opcode;
};

#endif /* _WORLDPACKET_H */
