#include<Windows.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;
//模板元编程 ;
template<unsigned n>
struct Factorial
{
	enum
	{
		value = n *Factorial<n-1>::value
	};
};
template<>//特殊情况Factorial<0>值为1;
struct Factorial<0>
{
	enum
	{
		value = 1
	};
};
//获取数组元素个数    
template<typename T,int n>    
int sizeofx(T (&arr)[n])    
{        
	return n;   
}         

//简单2进制    
template<int n>    
struct binaryx_    
{        
	enum
	{
		value = n % 10 + binaryx_<n / 10>::value * 2
	};   
};    
template<>    struct binaryx_<0>    
{        
	enum{value = 0};    
};

#if 0
int main()
{ 
	cout<<Factorial<10>::value<<endl;
//	cout<<binaryx_<20>::value<<endl;
	int kd[92];
	cout<<sizeofx(kd)<<endl;

	system("pause");
}
#endif