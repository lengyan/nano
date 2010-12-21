#include "ace/Log_Msg.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Configuration_Import_Export.h"
#include "ace/Reactor.h"
#include "ace/Acceptor.h"
#include "ClientService.h"
#include "utils/Config.h"

typedef ACE_Acceptor<ClientService, ACE_SOCK_ACCEPTOR> ClientAcceptor;

int ACE_TMAIN(int argc, ACE_TCHAR **argv) {
    u_int config_port;
    Config config;
    config.open("nano.ini");
    config.getInteger(ACE_TEXT("Global"), ACE_TEXT("port"), config_port);
	
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%i\n"), config_port));
    ACE_INET_Addr port(config_port);
	ClientAcceptor acceptor;
	if (acceptor.open(port) == -1) {
		return 1;
	}
	ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}
