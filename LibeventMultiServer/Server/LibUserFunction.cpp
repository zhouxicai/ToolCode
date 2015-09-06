#include "StdAfx.h"
#include "LibUserFunction.h"
#include "LibEvent.h"

CLibUserFunction::CLibUserFunction(void)
{
}

CLibUserFunction::~CLibUserFunction(void)
{
}

int CLibUserFunction::Connect(Conn* c)
{
	return 0;
}

int CLibUserFunction::DisConnect(Conn* c)
{
	return 0;
}

int CLibUserFunction::Login(Conn* c)
{
	Head *hreq =(Head*)c->in_buf;
	int nFreq=sizeof(Head)+sizeof(Proto_Login_Req);
	if (hreq->pkglen!=nFreq) 
	{
		return emFunReturClose;
	}
	Head *hrsp = (Head *) c->out_buf;
	hrsp->stx = hreq->stx;
	hrsp->nFunID = hreq->nFunID;
	hrsp->pkglen = sizeof(Head) + sizeof(Proto_Login_Rsp);
	Proto_Login_Rsp *lrsp = (Proto_Login_Rsp*) (c->out_buf + sizeof(Head));
	lrsp->uid=1;
	c->out_buf_len+=hrsp->pkglen ;
	return emFunReturnSend;
}

int CLibUserFunction::Logout(Conn* c)
{
	return emFunReturClose;
}
