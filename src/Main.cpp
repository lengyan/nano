#include "ace/Log_Msg.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Reactor.h"
#include "ace/Acceptor.h"
#include "ClientService.h"

typedef ACE_Acceptor<ClientService, ACE_SOCK_ACCEPTOR> ClientAcceptor;

int ACE_TMAIN(int argc, ACE_TCHAR **argv) {
	ACE_INET_Addr port(6060);
	ClientAcceptor acceptor;
	if (acceptor.open(port) == -1) {
		return 1;
	}
	ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}