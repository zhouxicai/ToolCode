#include "БъЭЗ.h"

int _tmain(int argc, _TCHAR* argv[])
{
	typedef  ACE_Acceptor<ACEServer, ACE_SOCK_ACCEPTOR> MyServer;
	ACE_INET_Addr address(12345);
	MyServer server;
	if (server.open(address) == -1) {
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Failed to Create Server/n"));
		return -1;
	}
	ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}