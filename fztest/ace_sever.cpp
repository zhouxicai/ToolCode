//服务器端代码。接收一个远端的连接，将接收到的信息打印在屏幕上，并将接收到的信息返回给客户端。
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
//	//设置服务器地址;
//	ACE_INET_Addr peer_addr( 5050, "127.0.0.1" );
//
//	ACE_SOCK_Stream peer_stream;
//
//	//创建被动连接角色对象;
//	ACE_SOCK_Acceptor peer_acceptor;
//	//开启被动连接对象，将对象绑定到一个地址上;
//	peer_acceptor.open( peer_addr );
//
//	//等待连接;
//	peer_acceptor.accept( peer_stream );
//
//	//数据通讯;
//	peer_stream.recv( (void*)str.c_str(), str.length() );
//	std::cout << "from client message : " << str << std::endl;
//	peer_stream.send( str.c_str(), str.length() );
//
//	ACE::fini();
//	return 0;
//}