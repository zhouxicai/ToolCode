#if 1
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <WinSock2.h>
//#include <sys/socket.h>  
//#include <netinet/in.h>  

#pragma comment(lib,"ws2_32.lib")


int main(int argc, char*argv[])
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addrSrv;
	memset(&addrSrv,0, sizeof(struct sockaddr_in));
	addrSrv.sin_addr.s_addr = inet_addr("192.168.1.107");

	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	sendto(sockfd, "client data", strlen("client data"), 0, (struct sockaddr*)&addrSrv, sizeof(struct sockaddr));

	char buf[1024] = { 0 };
	int len = sizeof(struct sockaddr);
	recvfrom(sockfd, buf, 1024, 0, (struct sockaddr*)&addrSrv, &len);
	printf("client recv:%s\n", buf);
	system("pause");
	close(sockfd);

	return 0;
}
#endif