//#include <iostream>
//#include <string>
//
//#include <../ACE_wrappers/ace/ACE.h>
//#include <../ACE_wrappers/ace/INET_Addr.h>
//#include <../ACE_wrappers/ace/SOCK_Connector.h>
//#include <../ACE_wrappers/ace/SOCK_Stream.h>
//
//int main( int argc, char* argv[] )
//{
//	ACE::init();//��ʼ��ACE�⣬��windows��һ��Ҫ;
//
//	std::string str = "hello world";
//
//	//���÷�������ַ;
//	//��һ�������Ƕ˿ڣ��ڶ�����ip��ַ��Ҳ����������;
//	//�����ȶ���һ����ַ��������ACE_INET_Addr��set�������趨;
//	//��ַ�����úܶ࣬����Ĳ����ĵ�;
//	ACE_INET_Addr peer_addr( 5050, "127.0.0.1" );
//	ACE_SOCK_Stream peer_stream;//����һ��ͨѶ����;
//
//	ACE_SOCK_Connector peer_connector;//����һ���������Ӷ���;
//	peer_connector.connect( peer_stream, peer_addr );//����һ������;
//
//	peer_stream.send( str.c_str(), str.length() );//�������ݵ�������;
//
//	str.erase();
//	str.resize( sizeof( "hello world" ) );
//	peer_stream.recv( (void*)str.c_str(), str.length() );//�������Է���������Ϣ;
//
//	std::cout << "from server message : " << str << std::endl;
//
//	ACE::fini();
//	return 0;
//} 
