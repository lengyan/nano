#include "World.h"
#include "ace/Log_Msg.h"
#include "ace/INET_Addr.h"
#include "ace/Configuration_Import_Export.h"
#include "ace/Reactor.h"
#include "ace/Acceptor.h"
#include "WorldSocket.h"
#include "utils/Config.h"


World::World() {

}
World::~World() {

}

// 初始化世界
int World::init() {
    u_int config_port;
    ACE_TString config_host;

    // 获取配置文件信息
    gConfig->getInteger(ACE_TEXT("Global"), ACE_TEXT("port"), config_port);
	gConfig->getString(ACE_TEXT("Global"), ACE_TEXT("host"), config_host);

    gLogger->log(LM_INFO, "start server in host %s, port %i\n", config_host.c_str(), config_port);
    ACE_INET_Addr listen_addr(config_port, config_host.c_str());
    WorldSocket::Acceptor acceptor;

    // 绑定端口
	if (acceptor.open(listen_addr) == -1) {
        gLogger->log(LM_ERROR, ACE_TEXT("open error\n"), config_port);
		return -1;
	}

	ACE_Reactor::instance()->run_reactor_event_loop();
}

// 世界运行
void World::run() {
}

/**
 * @brief   sendGlobalMessage 发送给所有人信息
 *
 * @param   worldPacket
 */
void sendGlobalMessage(WorldPacket* worldPacket) {


}

/**
 * @brief   update 世界更新
 */
void World::update() {
    // 这个要在哪里加锁?大循环外还是里面
    // 如果这里用锁的方式进行处理,这里假设获得锁,removeSession阻塞,但是实际上远端点已退出,那对其操作没意义
    // 所以用锁的话,还是不太好.最好是每次迭代,判断session的有效性,如果无效,删除之.
    // 此方案为mangoes方案
    WorldSession* session;
    // 处理所有会话
    for (SessionMap::iterator itr = sessionMap.begin(); itr != sessionMap.end(); itr++) {
        session = itr->second;
        // 会话更新,如果是假,则要删除这个会话了
        if (! session->update()) {
            removeSession(session->getUserId());
            delete session;
            session = NULL;
        }
    }
}

/**
 * @brief   addSession 增加会话
 *
 * @param   s
 */
void World::addSession(WorldSession* s) {
    sessionMap[s->getUserId()] = s;
}
/**
 * @brief   removeSession 删除会话
 *
 * @param   id
 */
void World::removeSession(uint32 id) {
    sessionMap.erase(id);
}
