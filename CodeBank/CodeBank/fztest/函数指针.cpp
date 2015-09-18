#include<Windows.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

int FunctionModle(void* v,bool b)
{
	cout<<"b:"<<b;
	return b;
}
struct MST
{
public:
	typedef int CommandModle(void*,bool);

	CommandModle* mCommand;
	MST(CommandModle* command):mCommand(command){}
	void print_num(){cout<<"MST!"<<endl;}
};

//int main()
//{
//	MST mst(&FunctionModle);
//	mst.print_num();
//	cout<<*mst.mCommand<<endl;
//			
//	system("pause");
//}