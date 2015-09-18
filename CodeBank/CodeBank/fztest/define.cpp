#include <iostream>
using namespace std;

#ifdef WIN32
#include <windows.h>
#else
#include<pthread.h>
#endif

void testx()
{
/********************************************************************/
#if 0
#define OUTPUT(word) cout<<#word<<endl;
#endif

#ifdef OUTPUT
	OUTPUT(HELLO me);
	OUTPUT(hello me);
#endif
/********************************************************************/
	int aabb = 100;
#define STRING(x) cout<<#x<<#x<<#x<<endl
		STRING(aab);
#ifdef TEXT
#define TEXT2(x) cout<<"system:"<<#x<<" Info"<<endl
		TEXT2(abb);
#endif

/********************************************************************/
#define UNIO(name) cout<<class##name<<endl
	int classaabb=910;
	UNIO(aabb);//组合变量;class+aabb=classaabb
#define UNIOSUP(x,y,z)cout<<x##y##z<<endl;
	int zhouxicai=99;
	UNIOSUP(zhou,xi,cai);//组合变量;
/********************************************************************/
	// 标准C预定义常量;
	cout<<__LINE__<<endl;//本行号,可用于定义错误代码后其他用途;
	cout<<__FILE__<<endl;//本代码所在文件;
	cout<<__DATE__<<endl;//被编译的日期;
	cout<<__TIME__<<endl;//被编译的时间;
	cout<<__TIMESTAMP__<<endl;//被编译的时间和日期;
	//	cout<<__STDC__<<endl;
#undef OUTPUT
/********************************************************************/
	system("pause");
}
/********************************************************************/
#if 0
void main()
{
	testx();

}
#endif

/********************************************************************/
#if 0
#define BeginProgram void main(int argc, char *argv[])
#define CloseBrace }
#define CommandLineArgument -1
#define Declare int i,j,n,Flag=1;
#define EndOfProgram return;
#define False 0;
#define ForLoop ;for
#define GetCommandLineArgument n=atoi(argv[1]);
#define i F1ag
#define If if
#define Increment ++
#define Is ==
#define LessThan *(c&64)*
#define LessThanOrEqualTo !=
#define Modulo %
#define OpenBrace {
#define PossibleFactor j
#define PossiblePrime i
#define Possib1ePrime (c=getchar())
#define PrimeNumber (c^(!i*n%64));
#define Print putchar
#define SetTo =
#define SmallestPrime 2
#define True 1
#define Variables char c;
#define Zero i%j

BeginProgram
	OpenBrace
	Declare Variables
	GetCommandLineArgument

	ForLoop (PossiblePrime SetTo SmallestPrime ;
Possib1ePrime LessThanOrEqualTo CommandLineArgument ;
Increment PossiblePrime)
	OpenBrace
	F1ag SetTo True
	ForLoop (PossibleFactor SetTo SmallestPrime ;
PossibleFactor LessThan PossiblePrime ;
Increment PossibleFactor)
	If (PossiblePrime Modulo PossibleFactor Is Zero)
	F1ag SetTo False

	If (Flag Is True)
	Print PrimeNumber
	CloseBrace

	EndOfProgram
	CloseBrace
#endif