//Client.cpp  
#include"БъЭЗ.h"  


ACE_Client_::ACE_Client_(char* hostname, int port) : remote_addr_(port, hostname)
{
	data_buf_ = "Hello from Client";
}

int ACE_Client_::connect_to_server()
{
	ACE_DEBUG((LM_DEBUG, "(%P | %T) Starting connect to %s:%d \n",
		remote_addr_.get_host_name(), remote_addr_.get_port_number()));

	if (connector_.connect(client_stream_, remote_addr_) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR, "(%p | %t) %p\n", "Connection failed"), -1);
	}
	else
	{
		ACE_DEBUG((LM_DEBUG, "(%P | %T) connected to %s\n", remote_addr_.get_host_name()));
	}

	return 0;
}

int ACE_Client_::send_to_server()
{
	for (int i = 0; i < NO_INTERATION; i++)
	{
		if (client_stream_.send_n(data_buf_, strlen(data_buf_) + 1, 0) == -1)
			ACE_ERROR_RETURN((LM_ERROR, "(%p | %t) %p\n", "send to"), 0);
		else
			ACE_DEBUG((LM_DEBUG, "(%T) Send Message to Server\n"));
	}

	close();
	return 0;
}

int ACE_Client_::close()
{
	if (client_stream_.close() == -1)
		ACE_ERROR_RETURN((LM_ERROR, "(%p | %t) %p \n", "close"), -1);
	else
		return 0;
}