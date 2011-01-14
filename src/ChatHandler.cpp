/**
 * @file ChatHandler.h
 * @brief   处理接收到的聊天信息
 * @author Dalton
 * @version 0.1
 * @date 2011-01-13
 */
#include <string>
#include "WorldSession.h"

void WorldSession::handleChat(WorldPacket& packet) {
    std::string s; 
    packet >> s;
    gLogger->debug("chat: %s\n", s.c_str());
}
