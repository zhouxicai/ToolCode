//�������˴��롣����һ��Զ�˵����ӣ������յ�����Ϣ��ӡ����Ļ�ϣ��������յ�����Ϣ���ظ��ͻ��ˡ�
//#include <iostream>
//#include <string>
//
//#include <../ACE_wrappers/ace/ACE.h>
//#include <../ACE_wrappers/ace/SOCK_Acceptor.h>
//#include <../ACE_wrappers/ace/SOCK_Stream.h>
//
//int main( int argc, char* argv[] )
//{
//	ACE::init();
//
//	std::string str;
//	str.resize( sizeof( "hello world" ) );
//
//	//���÷�������ַ;
//	ACE_INET_Addr peer_addr( 5050, "127.0.0.1" );
//
//	ACE_SOCK_Stream peer_stream;
//
//	//�����������ӽ�ɫ����;
//	ACE_SOCK_Acceptor peer_acceptor;
//	//�����������Ӷ��󣬽�����󶨵�һ����ַ��;
//	peer_acceptor.open( peer_addr );
//
//	//�ȴ�����;
//	peer_acceptor.accept( peer_stream );
//
//	//����ͨѶ;
//	peer_stream.recv( (void*)str.c_str(), str.length() );
//	std::cout << "from client message : " << str << std::endl;
//	peer_stream.send( str.c_str(), str.length() );
//
//	ACE::fini();
//	return 0;
//}