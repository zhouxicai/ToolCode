//Client
#include "ace/OS.h"
#include "ace/SOCK_Dgram.h"
#include "ace/INET_Addr.h"
#include "ace/Log_Msg.h"

#ifndef _DEBUG
#pragma comment(lib, "ace.lib")
#else
#pragma comment(lib, "aced.lib")
#endif

#define DATA_BUFFER_SIZE 1024
#define SIZE_DATA 29

class Client
{
public:
    Client(char * remote_host):remote_addr_(remote_host),local_addr_((u_short)0), local_(local_addr_)
    {
        data_buf = new char[DATA_BUFFER_SIZE];
        //remote_addr_.set_port_number(port);
    }

    //Receive data from the remote host using the datgram wrapper `local_¡¯.
    //The address of the remote machine is received in `remote_addr_¡¯
    //which is of type ACE_INET_Addr. Remember that there is no established
    //connection.
    int accept_data()
    {
        if (local_.recv(data_buf, SIZE_DATA, remote_addr_) != -1)
        {
            ACE_DEBUG((LM_DEBUG, "Data received from remote server %s was: %s \n",
                remote_addr_.get_host_name(), data_buf));
            return 0;
        }
        else
            return -1;
    }

    //Send data to the remote. Once data has been sent wait for a reply
    //from the server.
    int send_data()
    {
        ACE_DEBUG((LM_DEBUG, "Preparing to send data to server %s:%d\n",
            remote_addr_.get_host_name(), remote_addr_.get_port_number()));
        ACE_OS::sprintf(data_buf, "Client says hello");

        while (local_.send(data_buf, ACE_OS::strlen(data_buf), remote_addr_) != -1)
        {
            ACE_OS::sleep(1);
            if (accept_data() == -1)
                break;
            ACE_OS::sprintf(data_buf, "Client says hello");
        }

        return -1;
    }

private:
    char *data_buf;
    ACE_INET_Addr remote_addr_;
    ACE_INET_Addr local_addr_;
    ACE_SOCK_Dgram local_;
};

int main(int argc, char *argv[])
{
/*      if (argc<2)
    {
        ACE_OS::printf("Usage: %s <hostname:port_number> \n", argv[0]);
        ACE_OS::exit(1);
    }
*/    Client client("12345");
    client.send_data();
    system("pause");
    return 0;
}