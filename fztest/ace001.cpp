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
//	ACE::init();//初始化ACE库，在windows下一定要;
//
//	std::string str = "hello world";
//
//	//设置服务器地址;
//	//第一个参数是端口，第二个是ip地址，也可以是域名;
//	//可以先定义一个地址对象，再用ACE_INET_Addr的set函数来设定;
//	//地址的配置很多，具体的参照文档;
//	ACE_INET_Addr peer_addr( 5050, "127.0.0.1" );
//	ACE_SOCK_Stream peer_stream;//定义一个通讯队形;
//
//	ACE_SOCK_Connector peer_connector;//定义一个主动连接对象;
//	peer_connector.connect( peer_stream, peer_addr );//发起一个连接;
//
//	peer_stream.send( str.c_str(), str.length() );//发送数据到服务器;
//
//	str.erase();
//	str.resize( sizeof( "hello world" ) );
//	peer_stream.recv( (void*)str.c_str(), str.length() );//接收来自服务器的信息;
//
//	std::cout << "from server message : " << str << std::endl;
//
//	ACE::fini();
//	return 0;
//} 
