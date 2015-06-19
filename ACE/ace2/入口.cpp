//main  
#include "БъЭЗ.h" 


int main(int argc, char* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}

	ACE_Client_   client("wangj", 1234);
	client.connect_to_server();
	client.send_to_server();
	getchar();
	return 0;
}