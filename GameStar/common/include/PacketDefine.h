#ifndef _PACKET_DEFINE_H
#define _PACKET_DEFINE_H
	
/*packet declare*/
#define		REQUEST_REGISTER_ACCOUNT_NUMBER			1000
#define		RESPOND_REGISTER_ACCOUNT_NUMBER			1001

#define		REQUEST_LOGIN_SERVER					1002
#define		RESPOND_LOGIN_SERVER					1003

#define		REQUEST_PLAYER_MAP_POSITION				1010
#define		RESPOND_PLAYER_MAP_POSITION				1011

/*constant define*/
const unsigned short		ACCOUNT_NUMBER_NAME_MAX_SIZE			=	100;
const unsigned short		ACCOUNT_NUMBER_PASSWORD_MAX_SIZE		=	100;


/*packet body declare*/

typedef struct SPacketHead 
{
	unsigned short iPID;		//packet body id
	unsigned short iSize;		//packet body size
}stPACKET_HEAD,*pPACKET_HEAD;


/*packet body declare*/

//1000
typedef struct SRegisterAccountNumber
{
	char iName[ACCOUNT_NUMBER_NAME_MAX_SIZE];
	char iPassword[ACCOUNT_NUMBER_PASSWORD_MAX_SIZE];
}sREGISTER_ACCOUNT_NUMBER,*pREGISTER_ACCOUNT_NUMBER;


//1002
typedef struct SLoginServer
{
	char iName[ACCOUNT_NUMBER_NAME_MAX_SIZE];
	char iPassword[ACCOUNT_NUMBER_PASSWORD_MAX_SIZE];
}sLOGIN_SERVER,*pLOGIN_SERVER;


//1010
typedef struct SPlayerMapPosition
{
	int iPlayerID;
	int iX;
	int iY;
}sPLAYER_MAP_POSITION,*pPLAYER_MAP_POSITION;



#endif