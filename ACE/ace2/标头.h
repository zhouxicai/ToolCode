//Client.h:  
//ACE_Server.h  
#include"ace/SOCK_Connector.h" 
#include"ace/SOCK_Stream.h"  
#include"ace/Log_Msg.h"  
#include"ace/Time_Value.h"  

#include "ace/OS.h"
#include "ace/SOCK_Dgram.h"
#include "ace/INET_Addr.h"
#include "ace/Log_Msg.h"

#include "ace/OS_main.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/ACE.h"
#include "ace/SString.h"
#include "ace/Synch.h"
#include "ace/Synch_Traits.h"
#include "ace/OS_NS_stdio.h"
#include "ace/os_include/os_assert.h"

#define SIZE_BUF        128  
//#define SIZE_BUF        1024
#define NO_INTERATION   5  

class ACE_Client_
{
public:
	ACE_Client_(char* hostname, int port);
	int connect_to_server();
	int send_to_server();
	int close();

private:
	ACE_SOCK_Stream          client_stream_;
	ACE_INET_Addr        remote_addr_;
	ACE_SOCK_Connector  connector_;
	char*                           data_buf_;
};