//Server
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
    #define SIZE_DATA 19

    class Server
    {
	    public:
		        Server(int local_port)
			 : local_addr_(local_port), local_(local_addr_)
			        {
			            data_buf = new char[DATA_BUFFER_SIZE];
			        }
		
			
			       //Expect data to arrive from the remote machine. Accept it and display
			        //it. After receiving data, immediately send some data back to the
			       //remote.
			        int accept_data()
			        {
			            int byte_count = 0;
			            while ((byte_count = local_.recv(data_buf, SIZE_DATA, remote_addr_)) != -1)
			            {
			                data_buf[byte_count] = 0;
				             ACE_DEBUG((LM_DEBUG, "Data received from remote %s was %s \n", remote_addr_.get_host_name(), data_buf));
				                ACE_OS::sleep(1);
				                if (send_data() == -1) break;
				            }
			            return -1;
			        }
		
			        //Method used to send data to the remote using the datagram component
			        //local_
			        int send_data()
			        {
			            ACE_DEBUG((LM_DEBUG, "Preparing to send reply to client %s:%d\n",
			                remote_addr_.get_host_name(), remote_addr_.get_port_number()));
			            ACE_OS::sprintf(data_buf, "Server says hello to you too");
			            if (local_.send(data_buf, ACE_OS::strlen(data_buf) + 1, remote_addr_) == -1)
			                return -1;
			            else
			                return 0;
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
            ACE_DEBUG((LM_DEBUG, "Usage %s <Port Number>", argv[0]));
            ACE_OS::exit(1);
        }
*/    Server server(123456/*ACE_OS::atoi(argv[1])*/);
    server.accept_data();
    return 0;
}
