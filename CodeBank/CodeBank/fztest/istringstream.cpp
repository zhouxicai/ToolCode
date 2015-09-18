//istringstream对象可以绑定一行字符串，然后以空格为分隔符把该行分隔开来。

#include<iostream>
#include<sstream>
	using namespace std;

#pragma region test_function 

//定义多行语句为一行
#define DEBUG_STRING(p)				\
		if (!p)						\
		{							\
			cout<<p<<":error!";		\
		}else						\
		{							\
			cout<<endl<<"p:"<<p;	\
		};
void 测试定义多行语句为一行()
{
	DEBUG_STRING(2);
	DEBUG_STRING(0);
}

#pragma region 
void 分割字符串()
{
	string str="i an a boy";  
	istringstream is(str);  
	string s;  
	while(is>>s)  
	{  
	    cout<<s<<endl;  
	}  
}
void 分割字符串2()
{
	string str, line;
	while(getline(cin, line))
	{
		istringstream stream(line);
		while(stream>>line)
			cout<<line.c_str()<<endl;
	};	
}
#pragma endregion 分割字符串

#pragma endregion 

//int main()
//{
//	分割字符串();
//	
//	system("pause");
//	return 0;
//}