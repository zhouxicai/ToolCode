/******************************
����
# gcc -o test test.c -levent

����
# ./test

����һ�ն�����
# telnet 127.0.0.1 8080
*******************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <event.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>



static short ListenPort = 8080;
static long ListenAddr = INADDR_ANY;//�����ַ��ֵ����0
static int MaxConnections = 1024;
static int ServerSocket;
static struct event ServerEvent;//����event


//������ʲôƽ̨��д������򣬶�Ӧ��ʹ��NONBLOCK��һ��socket���óɷ�����ģʽ���������Ա�֤��ĳ������ٲ�����recv/send/accept/connect��Щ�����Ϸ���block�Ӷ��������������ͣ����
int SetNonblock(int fd)
{
    int flags;
    
    if ((flags = fcntl(fd, F_GETFL)) == -1) { //���������ļ���������һЩ����
        return -1;
    }

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        return -1;
    }

    return 0;
}

//����������ͻ��˵�socket�ɶ�ʱ��libevent����
void ServerRead(int fd, short ev, void *arg)
{
    struct client *client = (struct client *)arg;
    u_char buf[8196];
    int len, wlen;

    //��Ѳ���fd ��ָ���ļ�����count���ֽڵ�bufָ����ָ���ڴ���
    len = read(fd, buf, sizeof(buf));
    if (len == 0) {
        /* �ͻ��˶Ͽ����ӣ��������Ƴ����¼������ͷſͻ����ݽṹ */
        printf("disconnected\n");
        close(fd);
        event_del(&ServerEvent);
        free(client);
        return;
    } else if (len < 0) {
        /* �����������Ĵ���������ر�socket���Ƴ��¼������ͷſͻ����ݽṹ */
        printf("socket fail %s\n", strerror(errno));
        close(fd);
        event_del(&ServerEvent);
        free(client);
        return;
    }
    /* 
     Ϊ�˼�㣬����ֱ�ӽ�����д�ص��ͻ��ˡ�ͨ�����ǲ����ڷ�������Ӧ�ó�������ô����
       ����Ӧ�ý����ݷŵ������У��ȴ���д�¼���ʱ����д�ؿͻ��ˡ� 
     ���ʹ�ö���ն˽���socket���ӻ���ִ���socket fail Bad file descriptor
     */
    wlen = write(fd, buf, len);
    if (wlen < len) {
        printf("not all data write back to client\n");
    }

    return;
}

/*
   ����һ����������׼��������ʱ�������������libevent���ò����ݸ���������: 
   int fd:�����¼����ļ�������. 
   short event:�����¼�������EV_TIMEOUT,EV_SIGNAL, EV_READ, or EV_WRITE. 
   void* :��arg����ָ���ı���. 
*/
void ServerAccept(int fd, short ev, void *arg)
{
    int cfd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int yes = 1;
    int retval;

    //����������������л��������Ϣ�������µ��׽��֣������ظ��׽��ֵ��ļ���������
    //�´������׽������ڷ�������ͻ�����ͨ�ţ���ԭ�����׽�����Ȼ���ڼ���״̬��
    //�ú����ĵ�һ������ָ�����ڼ���״̬�����׽���
    cfd = accept(fd, (struct sockaddr *)&addr, &addrlen);
    if (cfd == -1) {
        printf("accept(): can not accept client connection");
        return;
    }
    if (SetNonblock(cfd) == -1) {
        close(cfd);
        return;
    }

    //������ĳ���׽��ֹ�����ѡ��
    //������ IPPROTO_TCP:TCPѡ��
    //������ TCP_NODELAY ��ʹ��Nagle�㷨 ѡ�������������ݶ����ǵȴ��������������Ȼ����һ�η���
    // �������TCP_NODELAY �� TCP_CORK
    //������ ��ѡ��TCP_NODELAY��ֵ
    if (setsockopt(cfd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
        printf("setsockopt(): TCP_NODELAY %s\n", strerror(errno));
        close(cfd);
        return;
    }

    event_set(&ServerEvent, cfd, EV_READ | EV_PERSIST, ServerRead, NULL);
    event_add(&ServerEvent, NULL);
    
    printf("Accepted connection from %s\n", inet_ntoa(addr.sin_addr));
}

int NewSocket(void)
{
    struct sockaddr_in sa;

    //socket����������һ���ܹ���������ͨ�ŵ��׽��֡�
    //��һ������ָ��Ӧ�ó���ʹ�õ�ͨ��Э���Э���壬����TCP/IPЭ���壬�ò�����AF_INET;
    //�ڶ�������ָ��Ҫ�������׽�������
    //���׽�������ΪSOCK_STREAM�����ݱ��׽�������ΪSOCK_DGRAM��ԭʼ�׽���SOCK_RAW
    //����������ָ��Ӧ�ó�����ʹ�õ�ͨ��Э�顣
    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ServerSocket == -1) {
        printf("socket(): can not create server socket\n");
        return -1;
    }

    if (SetNonblock(ServerSocket) == -1) {
        return -1;
    }

    //����ڴ�����
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    //htons��һ���޷��Ŷ�������ֵת��Ϊ�����ֽ���
    sa.sin_port = htons(ListenPort);
    //htonl���������޷��ų�������ת���������ֽ�˳��
    sa.sin_addr.s_addr = htonl(ListenAddr);

    //(struct sockaddr*)&sa��saǿ��ת��Ϊsockaddr���͵�ָ��
    /*struct sockaddr 
        ���ݽṹ����bind��connect��recvfrom��sendto�Ⱥ����Ĳ�����ָ����ַ��Ϣ��
        ��һ�����в���ֱ����Դ����ݽṹ����������ʹ����һ����sockaddr�ȼ۵����ݽṹ struct sockaddr_in
        sockaddr_in��sockaddr�ǲ��еĽṹ��ָ��sockaddr_in�Ľṹ���ָ��Ҳ����ָ��
        sockadd�Ľṹ�壬����������Ҳ����˵�������ʹ��sockaddr_in����������Ҫ����Ϣ,
        ������ý�������ת���Ϳ�����
    */
    //bind�������ڽ��׽��ְ󶨵�һ����֪�ĵ�ַ��
    if (bind(ServerSocket, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        close(ServerSocket);
        printf("bind(): can not bind server socket");
        return -1;
    }
    
    //ִ��listen ֮���׽��ֽ��뱻��ģʽ
    //MaxConnections ����������е���󳤶�,���������Ժ󣬽��ܾ��µ���������
    if (listen(ServerSocket, MaxConnections) == -1) {
        printf("listen(): can not listen server socket");
        close(ServerSocket);
        return -1;
    }

    /*
     event_set�Ĳ�����
     + ����1: ΪҪ������event
     + ����2: file descriptor����������ʱ������������Ϊ-1������evtimer_set���������
     + ����3: ����event���࣬���õ�EV_READ, EV_WRITE, EV_PERSIST, EV_SIGNAL, EV_TIMEOUT������ʱ�����øò���Ϊ0
     + ����4: event������֮�󴥷���callback����
     + ����5: ���ݸ�callback�����Ĳ���
     ��ע��
            �����ʼ��event��ʱ��������Ϊpersistent��(������EV_PERSIST)��
            ��ʹ��event_add������ӵ������¼����Ϻ�(pending״̬)��
            ��event���������pending״̬������event�������޴βμ�libevent���¼�������
            ÿ���䱻�����callback����ִ��֮�󣬸�event�Զ���activeת��Ϊpending״̬��
            �����μ�libevent������(�������������㣬�ֿ��Լ���ִ����callback)��
            �����ڴ�����ʹ��event_del()��������event��libevent�������¼�������ɾ����
            �����ͨ������EV_PERSISTʹ��event��persistent�ģ���Ҫ��event��callback���ٴε���event_add
            (����ÿ��pending��Ϊactive֮����callback���ٽ�������Ϊpending)
     */
    event_set(&ServerEvent, ServerSocket, EV_READ | EV_PERSIST, ServerAccept, NULL);
    //��event��ӵ�libevent�������¼�����
    if (event_add(&ServerEvent, 0) == -1) {
        printf("event_add(): can not add accept event into libevent");
        close(ServerSocket);
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int retval;
    
    event_init(); //��ʼ��event baseʹ��Ĭ�ϵ�ȫ��current_base
    
    retval = NewSocket();
    if (retval == -1) {
        exit(-1);
    }
    
    event_dispatch(); //�����¼�����ϵͳ����ʼ�����������ܣ�����
    
    return 0;
}