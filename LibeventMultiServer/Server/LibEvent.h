#pragma once
#include "CLibEventData.h"
#include "LibEventFunction.h"
#include "LibUserFunction.h"
class CLibEvent
{
public:
	CLibEvent(void);
	~CLibEvent(void);
private:
	//当前服务器对象
	Server m_Server;
public:
	bool StartServer(int port, short workernum, unsigned int connnum, int read_timeout, int write_timeout);
	void StopServer();
private:
	void LoadFuns();
	static void DoAccept(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *sa, int socklen, void *user_data);
	static void DoError(struct bufferevent *bev, short error, void *ctx);
	static void CloseConn(Conn *pConn,int nFunID);
	static void CloseConn(Conn *pConn);
	static void DoRead(struct bufferevent *bev, void *ctx);
	static DWORD WINAPI ThreadServer(LPVOID lPVOID);
	static DWORD WINAPI ThreadWorkers(LPVOID lPVOID);
};
