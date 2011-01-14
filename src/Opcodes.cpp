
#include "Opcodes.h"

OpcodeHandler opcodeTable[NUM_MSG_TYPES] = {
    { "CMSG_AUTH_SESSION"               , &WorldSession::handleNull },
    { "CMSG_CHAT_SAY"                   , &WorldSession::handleChat },
    { "SMSG_CHAT_SAY"                   , &WorldSession::handleNull },
    { "CMSG_CHAT_WHISPER"               , &WorldSession::handleChat },
    { "SMSG_CHAT_WHISPER"               , &WorldSession::handleNull }, 
    { "CMSG_CHAT_CHANNEL"               , &WorldSession::handleNull },
    { "SMSG_CHAT_CHANNEL"               , &WorldSession::handleNull },
    { "CMSG_CHAT_CHANNEL_JOIN"          , &WorldSession::handleNull }, 
    { "SMSG_CHAT_CHANNEL_JOIN"          , &WorldSession::handleNull },
    { "CMSG_CHAT_CHANNEL_LEAVE"         , &WorldSession::handleNull },
    { "SMSG_CHAT_CHANNEL_LEAVE"         , &WorldSession::handleNull },
    { "CMSG_CHAT_CHANNEL_LIST"          , &WorldSession::handleNull },
    { "SMSG_CHAT_CHANNEL_LIST"          , &WorldSession::handleNull },
};
