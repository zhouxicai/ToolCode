#include <tuple>

#include <iostream>
#include <Windows.h>
using namespace std::tr1;
//变量组，新一代pair，支持任意多个对象;
void tuple_test()
{
	//由构造函数初始化;
	std::tr1::tuple<int,char,float>tuple(1,'a',2.1);
	//由make_tuple初始化;
	std::tr1::tuple<int,char,float>tuple2 = std::tr1::make_tuple(1,'a',2.1);
	//由tie初始化;
	int a=1;int b=2;
	std::tr1::tuple<int,int>tuple3 =std::tr1::tie(a,b);
	//tuple中对象的数量;
//	std::tr1::tuple_size<tuple3>::value;
	//通过函数get可以返回一个tuple object中的一个元素的引用，所以可以对tuple object中特定的元素进行读和写的操作;
	std::tr1::get<0>(tuple3)=1;
}