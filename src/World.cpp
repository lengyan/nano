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
int World::init() {
    u_int config_port;
    ACE_TString config_host;

    sConfig->getInteger(ACE_TEXT("Global"), ACE_TEXT("port"), config_port);
	sConfig->getString(ACE_TEXT("Global"), ACE_TEXT("host"), config_host);

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("start server in host %s, port %i\n"), config_host.c_str(), config_port));
    ACE_INET_Addr listen_addr(config_port, config_host.c_str());
    WorldSocket::Acceptor acceptor;

	if (acceptor.open(listen_addr) == -1) {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("open error\n"), config_port));
		return -1;
	}

	ACE_Reactor::instance()->run_reactor_event_loop();
}

void World::run() {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("start reactor\n")));
	// ACE_Reactor::instance()->run_reactor_event_loop();
}

void World::addSession(WorldSession* s) {
    sessionList.push_back(s);
}
