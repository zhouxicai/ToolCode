
#include <stdio.h>
#include <tchar.h>
#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/Svc_Handler.h"
#define  _CRT_SECURE_NO_WARNINGS 


static const char * filename = "bigfile.dat";
// 服务器处理代码，每一个链接都要隐式生成这样一个的实例
class ACEServer : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
	typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super;
public:
	ACEServer() {
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Create New ACEServer/n"));
	};
public:
	virtual ~ACEServer() {
		ACE_DEBUG((LM_DEBUG, "(%P|%t) Destory ACEServer/n"));
	};
	virtual int open(void *p){
		if ((file = fopen(filename, "rb")) == NULL) {
			ACE_DEBUG((LM_DEBUG, "(%P|%t) Failed to open file/n"));
			return -1;
		}
		total = 0;
		ACE_DEBUG((LM_DEBUG, "(%P|%t) New Client Connection/n"));
		// 要注册写事件
		ACE_Reactor::instance()->register_handler(this,
			ACE_Event_Handler::WRITE_MASK);
		return super::open(p);
	}
protected:
	virtual int handle_output(ACE_HANDLE) {
		size_t count = fread(block, sizeof(char), sizeof(block), file);
		// 没有内容了，就注销
		if (count <= 0) {
			ACE_DEBUG((LM_DEBUG, "/n(%P|%t) Send Finished!/n"));
			fclose(file);
			file = NULL;
			return -1;
		}
		this->peer().send(block, count);
		total += count;
		ACE_DEBUG((LM_DEBUG, ".", total));
		return 1;
	}
private:
	char block[4096];
	FILE *file;
	size_t total;
};