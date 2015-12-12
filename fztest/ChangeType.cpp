class A
{
	volatile int b;
//	A():b(1){}
};
//×ª»»³£Á¿;
void change()
{
	volatile const A* a = new A;
	A* aa = const_cast<A*>(a);

	const A a2;
	A aaa = const_cast<A&>(a2);
	A &aaaa = const_cast<A&>(a2);

	const int tt = 9;
	int bt = static_cast<int>(tt) ;


}