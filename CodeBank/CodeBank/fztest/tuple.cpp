#include <tuple>

#include <iostream>
#include <Windows.h>
using namespace std::tr1;
//�����飬��һ��pair��֧������������;
void tuple_test()
{
	//�ɹ��캯����ʼ��;
	std::tr1::tuple<int,char,float>tuple(1,'a',2.1);
	//��make_tuple��ʼ��;
	std::tr1::tuple<int,char,float>tuple2 = std::tr1::make_tuple(1,'a',2.1);
	//��tie��ʼ��;
	int a=1;int b=2;
	std::tr1::tuple<int,int>tuple3 =std::tr1::tie(a,b);
	//tuple�ж��������;
//	std::tr1::tuple_size<tuple3>::value;
	//ͨ������get���Է���һ��tuple object�е�һ��Ԫ�ص����ã����Կ��Զ�tuple object���ض���Ԫ�ؽ��ж���д�Ĳ���;
	std::tr1::get<0>(tuple3)=1;
}