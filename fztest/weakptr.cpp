//weak_ptr���ô� ;
//����ʱʹ�� shared_ptr;
//ʹ����ʹ�� weak_ptr ;
//��ֹ����Ӧ�õ�������ʧ�� ;
#include <cstdlib>
#include <vector>
#include <iostream>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
using namespace std;
using namespace boost;
class B;
class A
{
	//shared_ptr<B> m_value;//���������������������� ;
	boost::weak_ptr<B> m_value;    //��������������������; 
public:
	string str; 
	A(){str = "A";cout<<"A ����;"<<endl;}
	void SetValue(boost::shared_ptr<B> p){m_value = p;}
	boost::weak_ptr<B> GetData(){return m_value;}
	~A(){cout<<"A ����;"<<endl;}
};
class B
{
	//shared_ptr<A> m_value;//���������������������� ;
	boost::weak_ptr<A> m_value;    //�������������������� ;
public:
	string str; 
	B(){str = "A";cout<<"B ����;"<<endl;}
	void SetValue(boost::shared_ptr<A> p){m_value = p;}
	boost::weak_ptr<A> GetData(){return m_value;}
	~B(){cout<<"B ����;"<<endl;}
}; 
void Do()
{
	cout<<"-----------------------------"<<endl;
	boost::shared_ptr<A> a(new A);
	boost::shared_ptr<B> b(new B);
	a->SetValue(b);
	b->SetValue(a);
	boost::weak_ptr<B> bb = a->GetData();
	if(bb.expired())
	{	
		//cout<<bb->lock().get()->str<<endl;
	}
	cout<<"-----------------------------"<<endl;
}

// std_tr1__memory__weak_ptr_lock.cpp 
// compile with: /EHsc 
#include <memory> 
#include <iostream> 

struct deleter 
{ 
	void operator()(int *p) 
	{ 
		delete p; 
	} 
}; 

//int main() 
//{ 
//	std::weak_ptr<int> wp; 
//	{ 
//		std::shared_ptr<int> sp(new int(10)); 
//		wp = sp; 
//		std::cout << "wp.expired() == " << std::boolalpha 
//			<< wp.expired() << std::endl; 
//		std::cout << "*wp.lock() == " << *wp.lock() << std::endl; 
//	} 
//
//	// check expired after sp is destroyed 
//	std::cout << "wp.expired() == " << std::boolalpha 
//		<< wp.expired() << std::endl; 
//	std::cout << "(bool)wp.lock() == " << std::boolalpha 
//		<< (bool)wp.lock() << std::endl; 
//
//	system("PAUSE");
//	return (0); 
//} 

//int main(int argc, char *argv[])
//{
//	Do();
//	system("PAUSE");
//	return EXIT_SUCCESS;
//}

/*
scoped_ptr�ǲ��ܺ� weak_ptr,shared_ptr����ת���ģ���Ϊû����Ӧ��ת��������;

�������ǹ�������������������Ҳ���Լ�����scope:���õ������������˾�û���ˡ�ͬʱ������������Ȩ�ֶ�ռ����;

shared_ptr�����԰�weak_ptrת���ɣ���ֵ����shared_ptr���������ָ�ֵ���ᵼ��weak_ptr�����ü������ӡ� �������ǰ�weak_ptr�����ü�������shared_ptr�����ü�����

Ҳ���԰�shared_ptrת���ɣ���ֵ����weak_ptr���������ָ�ֵ���ᵼ��shared_ptr�����ü������ӡ� �������ǰ�shared_ptr�����ü�������weak_ptr�����ü�����

shared_ptr<int> pi1(new int910));

int *p1=pi1.get();

pi1=p1;//error..

weak_ptr<int>  wp=weak_ptr<int>( pi1.get() );

pi1 = wp;//ok

��ʶweak_ptr�ĺ÷���������Ϊ ����һ���ָ��û�����𣬻��о�����û��ɾ�����ܷ��ʵĶ�̬����Ŀռ�������������ڵ�Ŀ���� ���� pi1 = wp;//ok ���Խ��С�

��Ϊ������ָ�������ڣ�;

����ָ��<Type> ָ��Type������ָ����� ;

Type * p= new Type;

ָ��Type������ָ����� = p �Ǵ���ģ�;

���ϣ�shared_ptr ,�� weak_ptr������Ի��ำֵ��scoped_ptr�ǹ����ģ�;

weak_ptr��Ȩ�ͷ����ܷ��ʵĶ�̬����Ŀռ䡣

���ԣ�;

main(){ weak_ptr<int> wp(new int(10) );}���ᵼ���ڴ�й¶

main()

{                      weak_ptr<int> wp(new int(10) );

shared_ptr<int> sp=wp;//����ı����ü���

}//�������ڴ�й¶

//����ʲô�����ת�����Խ��п��Բο�bootԴ���롣;

*/