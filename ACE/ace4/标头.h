#include <stdio.h>
#include <tchar.h>
#include <ace/Connector.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/Svc_Handler.h>
// 客户端，获取服务器的文件内容
class ACEClient : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
	typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super;
public:
	ACEClient() {
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Create New ACEClient/n"));
	};
public:
	virtual ~ACEClient() {
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Destory ACEClient/n"));
	};
	virtual int open(void *p){
		total = 0;
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Connected to Server/n"));
		return super::open(p);
	}
protected:
	// 处理服务器发过来的内容
	virtual int handle_input(ACE_HANDLE) {
		int count = this->peer().recv(block, sizeof(block));
		if (count > 0) {
			total += count;
			ACE_DEBUG((LM_DEBUG, "(%P|%t) Received %d bytes/n", total));
			return 0;
		}
		// 结束了，停止反应器
		if (count == 0 && ACE_OS::last_error() != EWOULDBLOCK) {
			ACE_Reactor::instance()->end_reactor_event_loop();
			return -1;
		}
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Received %d bytes/n", total));
		return 0;
	}
private:
	char block[4096];
	size_t total;
};