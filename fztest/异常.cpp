#pragma warning (disable:4290)
#include <iostream>

using namespace std;
class cerror
{//异常类，错误类型综合定义;
public:
	cerror(int etime):et(etime){}
	int GetTime()const{return et;}

private:
	int et;
};
/******************************************************/
void yichang()
{
	int speed = 0;
	int time = 0;
	int space = 0;
	const int stdtime = 5;

	try
	{
		space = 0;
		time = 10;
		if (time<=0)
		{//抛出自定义异常类;
			throw cerror(time);
		}
		if (space<=0)
		{
			throw space;
		}
		//处理正常情况;
		speed = space/time;
		cout<<"速度为;"<<speed<<endl;
	}
	catch(cerror e)
	{//处理异常情况;
		cout<<"有些意外！他的用的时间为;"<<e.GetTime()<<endl;
		speed = space/stdtime;
		cout<<"估计他的速度大概在每分钟;"<<speed<<"米左右;"<<endl;		
	}
	catch(int se)
	{//处理异常情况;
		cout<<"有些意外！他的移动的距离为;"<<se<<endl;
	}
	catch(...)
	{//处理其他异常情况;

	}
}
/******************************************************/
inline void ErrorLine(){cout<<__LINE__<<"行出错;"<<endl;} //用C++方法,逻辑错误，出错行都在本行;
#define ERROR_LINE cout<<__LINE__<<"行出错"<<endl //用C式宏，逻辑正确，错误行都在替换位置;
void yichang2()throw(int,double);//声明该函数抛出异常类型;
void yichang2()throw(int,double)
{
	int x=0; double y=10;
	if (x==0&&y==0)
	{	//在函数内部抛出异常;	
		ERROR_LINE;throw (x,y);//可同时抛出多个值，用逗号隔开;
	}
	if (x==0)
	{	//在函数内部抛出异常;	
		ERROR_LINE;throw x;
	}
	if (y==0) 
	{
		ERROR_LINE;throw y;
	}
	return ;
}
/******************************************************/
void test()throw();//声明该函数不会抛出任何异常
void test()throw()
{
	try
	{
		yichang2();
	}
	catch (int x)
	{
		cout<<"有些意外！x为;"<<x<<endl;		
	}
	catch (double y)
	{
		cout<<"有些意外！y为;"<<y<<endl;		
	}

}
/******************************************************/
#include <new> 
using std::bad_alloc;
struct node
{
	int data;
	node * link;
};
void test2()throw(bad_alloc);
void test2()throw(bad_alloc)
{
	try
	{	
		node* x = new node;
	}//分配内存失败时内部抛出bad_alloc指令
	catch (bad_alloc)
	{
		cout<<"有些意外！内存分配失败;"<<endl;		
	}

	
}
/******************************************************/
#if 0
void main()throw()
{
	test();
	yichang();
	system("pause");
}
#endif
//抛出一个异常使你能够将控制流从程序中的任何地方转换到任何其他地方,类似goto语句，建议保守使用异常;
//异常处理机制可以使你在程序设计时，将异常处理的代码与正常处理的代码隔离开。;
//throw也可以在没有包含try模块的函数中使用抛出值。此时，该函数可在try模块调用。;

//同时抛出两个异常的catch处理问题。;
//自定义异常类未具体实践。;