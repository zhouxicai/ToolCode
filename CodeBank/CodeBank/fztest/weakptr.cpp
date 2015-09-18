//weak_ptr的用处 ;
//创建时使用 shared_ptr;
//使用是使用 weak_ptr ;
//防止互相应用导致析构失败 ;
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
	//shared_ptr<B> m_value;//析构函数将不能正常析构 ;
	boost::weak_ptr<B> m_value;    //析构函数将能正常析构; 
public:
	string str; 
	A(){str = "A";cout<<"A 构造;"<<endl;}
	void SetValue(boost::shared_ptr<B> p){m_value = p;}
	boost::weak_ptr<B> GetData(){return m_value;}
	~A(){cout<<"A 析构;"<<endl;}
};
class B
{
	//shared_ptr<A> m_value;//析构函数将不能正常析构 ;
	boost::weak_ptr<A> m_value;    //析构函数将能正常析构 ;
public:
	string str; 
	B(){str = "A";cout<<"B 构造;"<<endl;}
	void SetValue(boost::shared_ptr<A> p){m_value = p;}
	boost::weak_ptr<A> GetData(){return m_value;}
	~B(){cout<<"B 析构;"<<endl;}
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
scoped_ptr是不能和 weak_ptr,shared_ptr进行转换的，因为没有相应的转换函数！;

所以他是孤立，这点从他的名字上也可以见到。scope:作用地域，领域。来开了就没有了。同时在领域内所有权又独占！！;

shared_ptr：可以把weak_ptr转化成（赋值给）shared_ptr：而且这种赋值不会导致weak_ptr的引用计数增加。 而仅仅是把weak_ptr的引用计数赋给shared_ptr的引用计数。

也可以把shared_ptr转化成（赋值给）weak_ptr。而且这种赋值不会导致shared_ptr的引用计数增加。 而仅仅是把shared_ptr的引用计数赋给weak_ptr的引用计数。

shared_ptr<int> pi1(new int910));

int *p1=pi1.get();

pi1=p1;//error..

weak_ptr<int>  wp=weak_ptr<int>( pi1.get() );

pi1 = wp;//ok

认识weak_ptr的好方法就是认为 他和一般的指针没有区别，还有就是他没有删除它能访问的动态分配的空间的能力。它存在的目的是 他让 pi1 = wp;//ok 可以进行。

因为在智能指针领域内：;

智能指针<Type> 指向Type的智能指针对象 ;

Type * p= new Type;

指向Type的智能指针对象 = p 是错误的！;

综上：shared_ptr ,和 weak_ptr对象可以互相赋值。scoped_ptr是孤立的！;

weak_ptr无权释放他能访问的动态分配的空间。

所以：;

main(){ weak_ptr<int> wp(new int(10) );}将会导致内存泄露

main()

{                      weak_ptr<int> wp(new int(10) );

shared_ptr<int> sp=wp;//不会改变引用计数

}//不会有内存泄露

//关于什么情况下转换可以进行可以参看boot源代码。;

*/