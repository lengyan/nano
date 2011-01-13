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

// 世界更新
void World::update() {
    WorldSession* session;
    // 处理消息队列
    while (sessionDeque.next(session)) {
        session->update();
    }
}

// 增加会话
void World::addSession(WorldSession* s) {
    sessionDeque.add(s);
}
