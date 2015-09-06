#pragma once
typedef enum HeadStx
{
	emStx=860805
};
typedef enum emConfig
{
	emMaxBuffLen=4096,
	emMaxPackageType=65535
};
//�����
typedef enum emFunID
{
	emFunNull=-1,
	emFunClosed=0,
	emFunTimeout=1,
	emFunError=2,
	emFunConnected=3,
	emFunBase=1000,
	emFunLogin=1001,
	emFunLogout=1002
};
typedef enum emFunReturn
{
	emFunReturClose=1,
	emFunReturnSend,
	emFunReturnRecv
};
/************************************************************************/
/* ��ͷ                                                                 */
/************************************************************************/
typedef struct _Head 
{
	int stx;
	short pkglen;
	short nFunID;
}Head,*PHead;

/************************************************************************/
/* �û���¼Э��                                                         */
/************************************************************************/
typedef struct _Proto_Login_Req
{
	short uid;
}Proto_Login_Req,*PProto_Login_Req;

typedef struct _Proto_Login_Rsp
{
	short uid;
}Proto_Login_Rsp,*PProto_Login_Rsp;
/************************************************************************/
/* �ǳ�Э��                                                             */
/************************************************************************/
typedef struct _ProtoLogout_Req
{
}ProtoLogout_Req,*PProtoLogout_Req;