#pragma warning (disable:4290)
#include <iostream>

using namespace std;
class cerror
{//�쳣�࣬���������ۺ϶���;
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
		{//�׳��Զ����쳣��;
			throw cerror(time);
		}
		if (space<=0)
		{
			throw space;
		}
		//�����������;
		speed = space/time;
		cout<<"�ٶ�Ϊ;"<<speed<<endl;
	}
	catch(cerror e)
	{//�����쳣���;
		cout<<"��Щ���⣡�����õ�ʱ��Ϊ;"<<e.GetTime()<<endl;
		speed = space/stdtime;
		cout<<"���������ٶȴ����ÿ����;"<<speed<<"������;"<<endl;		
	}
	catch(int se)
	{//�����쳣���;
		cout<<"��Щ���⣡�����ƶ��ľ���Ϊ;"<<se<<endl;
	}
	catch(...)
	{//���������쳣���;

	}
}
/******************************************************/
inline void ErrorLine(){cout<<__LINE__<<"�г���;"<<endl;} //��C++����,�߼����󣬳����ж��ڱ���;
#define ERROR_LINE cout<<__LINE__<<"�г���"<<endl //��Cʽ�꣬�߼���ȷ�������ж����滻λ��;
void yichang2()throw(int,double);//�����ú����׳��쳣����;
void yichang2()throw(int,double)
{
	int x=0; double y=10;
	if (x==0&&y==0)
	{	//�ں����ڲ��׳��쳣;	
		ERROR_LINE;throw (x,y);//��ͬʱ�׳����ֵ���ö��Ÿ���;
	}
	if (x==0)
	{	//�ں����ڲ��׳��쳣;	
		ERROR_LINE;throw x;
	}
	if (y==0) 
	{
		ERROR_LINE;throw y;
	}
	return ;
}
/******************************************************/
void test()throw();//�����ú��������׳��κ��쳣
void test()throw()
{
	try
	{
		yichang2();
	}
	catch (int x)
	{
		cout<<"��Щ���⣡xΪ;"<<x<<endl;		
	}
	catch (double y)
	{
		cout<<"��Щ���⣡yΪ;"<<y<<endl;		
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
	}//�����ڴ�ʧ��ʱ�ڲ��׳�bad_allocָ��
	catch (bad_alloc)
	{
		cout<<"��Щ���⣡�ڴ����ʧ��;"<<endl;		
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
//�׳�һ���쳣ʹ���ܹ����������ӳ����е��κεط�ת�����κ������ط�,����goto��䣬���鱣��ʹ���쳣;
//�쳣������ƿ���ʹ���ڳ������ʱ�����쳣����Ĵ�������������Ĵ�����뿪��;
//throwҲ������û�а���tryģ��ĺ�����ʹ���׳�ֵ����ʱ���ú�������tryģ����á�;

//ͬʱ�׳������쳣��catch�������⡣;
//�Զ����쳣��δ����ʵ����;