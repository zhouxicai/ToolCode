//ACE_Server.cpp  
#include"БъЭЗ.h"  
//#include"ACE_Server.h"  

ACE_Server::ACE_Server(int port) : server_addr_(port), peer_acceptor_(server_addr_)
{
	data_buf_ = new char[SIZE_BUF];
}

ACE_Server::~ACE_Server()
{
	delete[]data_buf_;
	data_buf_ = NULL;
}

int ACE_Server::handle_connection()
{
	for (int i = 0; i < NO_INTERATION; i++)
	{
		int byte_count = 0;
		if ((byte_count = new_stream_.recv(data_buf_, SIZE_DATA, 0)) == -1)
		{
			ACE_ERROR((LM_ERROR, "%p\n", "Error in recv"));
		}
		else
		{
			data_buf_[byte_count] = '\0';
			ACE_DEBUG((LM_DEBUG, "Server received %s \n", data_buf_));
		}

	}

	if (new_stream_.close() == -1)
		ACE_ERROR((LM_ERROR, "%p\n", "Close Error"));

	return 0;
}

int ACE_Server::accept_connections()
{
	if (peer_acceptor_.get_local_addr(server_addr_) == -1)
		ACE_ERROR_RETURN((LM_ERROR, "%p \n", "Error in get_local_addr"), 1);

	ACE_DEBUG((LM_DEBUG, "Starting server at port: %d \n", server_addr_.get_port_number()));

	while (1)
	{
		ACE_Time_Value timeout(ACE_DEFAULT_TIMEOUT);
		if (peer_acceptor_.accept(new_stream_, &client_addr_, &timeout) == -1)
		{
			ACE_ERROR((LM_ERROR, "%p \n", "Accept"));
			continue;
		}
		else
		{
			ACE_DEBUG((LM_DEBUG, "Connection established with remote %s : %d \n",
				client_addr_.get_host_name(), client_addr_.get_port_number()));

			handle_connection();
		}
	}
}