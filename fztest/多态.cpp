#include <iostream>
//Effective c++ study;
class CBase
{
public://可以在类中和类外(用对象)调用;
	virtual void Object()=0{std::cout<<"pure virtual function Can have function body!"<<std::endl;};//纯虚函数，只继承接口;
	virtual void ImpureVirtual(){std::cout<<"base class:ImpureVirtual!"<<std::endl;};	//虚函数，继承接口和一份缺省实现;
	void BaseSomething(){std::cout<<"base class:BaseSomething!"<<std::endl;};			//非虚函数,继承接口和一份强制实现;
	
	void UsePrivateVirtual(CBase & obj)
	{//条款35非虚函数接口(NVI)手法，条款37-例子P183;
		//dosomething,可以做锁定互斥器等事前工作;
		obj.private_virtual();//如果让客户直接调用虚函数，就没有任何好办法可以做其他事情;
		//dosomething，可以解锁互斥器等事后工作;
	}
private://只能在本类中调用;
	virtual void private_virtual(){std::cout<<"CBase:private_virtual!"<<std::endl;};//NVI手法,派生类可以重新定义它;
protected://可以在派生类中调用，不能再类外调用;

};

class CDerivedX :public CBase
{
public:
	virtual void Object(){std::cout<<"CDerivedX!"<<std::endl; CBase::Object();/*可以调用纯虚函数的定义*/};
	void Something(){std::cout<<"CDerivedX:something!"<<std::endl;};
private:
	virtual void private_virtual(){std::cout<<"CDerivedX:private_virtual!"<<std::endl;};
protected:

};
void obj(CBase & obj)
{	//动态绑定，多态调用对应函数;
	obj.Object();
}
#if 0
int main()
{	
	CDerivedX ca;
	//多态惯用法;
	obj(ca);
	//调用自己特有函数;
	ca.Something();
	//调用基类特有函数;
	ca.BaseSomething();
	//NVI手法，调用基类的非虚函数，间接调用本类虚函数;
	ca.UsePrivateVirtual(ca);
	system("pause");
}
#endif
/*
1.纯虚类不能实例化;
2.纯虚函数也可以有函数体,但是这破坏了三层继承类型;
3.如果成员函数是个非虚函数，意味着它并不打算在派生类中有不同的行为;
4.非虚函数代表的意义是不变性，应该避免在派生类中重新定义;

5.虚函数，可以在派生类中选择是否重写;
6.纯虚函数则强制要求派生类必须重写;
7.非虚函数则是强制继承到派生类中，除非被同名函数覆盖;
8.绝不重复定义继承而来的虚函数的参数,因为参数是静态绑定的，而虚函数是动态绑定的，所以不匹配;
 */