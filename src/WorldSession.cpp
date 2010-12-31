#include "WorldSession.h"

WorldSession::WorldSession(ACE_UINT32 accountId):id(accountId) {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("init %d\n"), id));
}
WorldSession::~WorldSession() {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("destory %d\n"), id));
}
/**
 * 会话更新
 * */
void WorldSession::update() {

}

/**
 * 加入消息队列
 * */
void WorldSession::pushMessage() {

}

void WorldSession::echo() {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("echo %d\n"), id));
}
