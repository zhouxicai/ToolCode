//istringstream������԰�һ���ַ�����Ȼ���Կո�Ϊ�ָ����Ѹ��зָ�������

#include<iostream>
#include<sstream>
	using namespace std;

#pragma region test_function 

//����������Ϊһ��
#define DEBUG_STRING(p)				\
		if (!p)						\
		{							\
			cout<<p<<":error!";		\
		}else						\
		{							\
			cout<<endl<<"p:"<<p;	\
		};
void ���Զ���������Ϊһ��()
{
	DEBUG_STRING(2);
	DEBUG_STRING(0);
}

#pragma region 
void �ָ��ַ���()
{
	string str="i an a boy";  
	istringstream is(str);  
	string s;  
	while(is>>s)  
	{  
	    cout<<s<<endl;  
	}  
}
void �ָ��ַ���2()
{
	string str, line;
	while(getline(cin, line))
	{
		istringstream stream(line);
		while(stream>>line)
			cout<<line.c_str()<<endl;
	};	
}
#pragma endregion �ָ��ַ���

#pragma endregion 

//int main()
//{
//	�ָ��ַ���();
//	
//	system("pause");
//	return 0;
//}