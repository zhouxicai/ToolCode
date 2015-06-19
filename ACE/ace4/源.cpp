#include "БъЭЗ.h"

int _tmain(int argc, _TCHAR* argv[])
{
	typedef ACE_Connector<ACEClient, ACE_SOCK_CONNECTOR> MyClient;
	ACE_INET_Addr address(12345, "localhost");
	MyClient client;
	ACEClient c;
	ACEClient *pc = &c;
	if (client.connect(pc, address) == -1) {
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Failed to connect server!/n"));
		return -1;
	}
	ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}