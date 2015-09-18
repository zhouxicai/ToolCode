
//条款33;
class CBaseA
{
public:
	void set(double x){};
	void set(int x){};
};

class CDerived :public CBaseA
{
public:
	using CBaseA::set;//绕过同名非虚函数被遮盖;
	void set(int x)//如果不用上下两个方法，基类的同名函数在派生类中将不可见（被遮盖），除非用虚函数;
	{CBaseA::set(x);};//转交函数，绕过遮盖;
};

void used()
{
	
	CDerived de;
	de.set(2);
	de.set(3.3);
}
//int main()
//{
//
//}
//派生类的名称会遮盖基类中的同名函数;
/*

*/