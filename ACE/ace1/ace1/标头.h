//ACE_Server.h  
#include"ace/SOCK_Acceptor.h"  
#include"ace/SOCK_Stream.h"  
#include"ace/Log_Msg.h"  
#include"ace/Time_Value.h"  

#define SIZE_DATA       18  
//#define SIZE_BUF        1024  
#define SIZE_BUF        128  
#define NO_INTERATION   5  

class ACE_Server
{
public:
	ACE_Server(int port);
	~ACE_Server();
	int handle_connection();
	int accept_connections();

private:
	char *data_buf_;
	ACE_INET_Addr server_addr_;
	ACE_INET_Addr client_addr_;
	ACE_SOCK_Acceptor peer_acceptor_;
	ACE_SOCK_Stream new_stream_;
};