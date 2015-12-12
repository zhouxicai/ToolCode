#include<Windows.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include <list>
#include <map>
#include <hash_map>
#include <unordered_map>
#include <algorithm>
using namespace std;
using namespace tr1;
//*******************************************************
//vector��ȷɾ��Ԫ��;
vector<int> vi;
void removedata(int data)
{	//��ʵɾ��;
	vi.erase(remove(vi.begin(),vi.end(),data),vi.end());
}
void VectorTest()
{	//vi()Ԥ����size()��С,������reserve����
	vi.reserve(100);//Ԥ�����capacity()��С
	cout<<"vi.size:"<<vi.size()<<endl;
	cout<<"vi.capacity:"<<vi.capacity()<<endl;
	
	for (int i=0;i<100;i++)
	{
		vi.push_back(i);
	}
	cout<<"vi.size:"<<vi.size()<<endl;
	cout<<"vi.capacity:"<<vi.capacity()<<endl;
	
	removedata(99);
	removedata(55);
	removedata(11);
	for (int j=10;j<20;j++)
	{	//����ɾ��������������ɾ����vi.size��С����;
		remove(vi.begin(),vi.end(),j);
	}

//	vector<int>::iterator vii =vi.begin()��ʽ�÷�;
	for (auto i=vi.begin();i!=vi.end();i++)
	{
		cout<<*i<<endl;
	}
	cout<<"vi.size:"<<vi.size()<<endl;
	cout<<"vi.capacity:"<<vi.capacity()<<endl;
}
//*******************************************************
list<int> li;
void ListTest()
{	cout<<"li.size:"<<li.size()<<endl;
	for (int i=0;i<100;i++)
	{
		li.push_back(i);
	}
	cout<<"init li"<<endl;
	cout<<"li.size:"<<li.size()<<endl;
	li.remove(33);
	cout<<"remove li one number"<<endl;
	cout<<"li.size:"<<li.size()<<endl;
//	list<int>::iterator lii;
	for (auto lii=li.begin();lii!=li.end();lii++)
	{
		cout<<"list cout:"<<*lii<<endl;
	}
	cout<<"li.size:"<<li.size()<<endl;
	cout<<"delete li"<<endl;
	//li.erase(li.begin(),li.end());//ɾ����������֮���Ԫ��;
	li.clear();//ɾ��ȫ��Ԫ��;
	cout<<"li.size:"<<li.size()<<endl;

}
//*******************************************************
template<class T> 
struct increment : public unary_function<T, void> 
{ 
	void operator()(T& x)
	{
		x++;
	}

}; 

void ForEach()
{
	int nums[] = {3, 4, 2, 9, 15, 267};
	const int N = 6;

	cout << "Before, nums[] is: ";
	for (int i = 0; i < N; i++) {
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;

	std::for_each(nums, nums + N, increment<int>());

	std::cout << "After, nums[] is: ";
	for (int i = 0; i < N; i++) {
		std::cout << nums[i] << " ";
	}

}
//*******************************************************
//for_each����;
class couttest
{
public:
	void	printcout()
	{
		std::cout << "pint cout \n"<<endl;
	}
};

void tscouttest()
{
	
	list<couttest>  ml;
	int i =0;
	

	while (i!=10)
	{
		couttest ct;	
		ml.push_back(ct);
		++i;
	}
	for_each(ml.begin(),ml.end(),mem_fun_ref(&couttest::printcout));
}
#include <string>
void mtdd()
{
	typedef std::pair<int,double> pair_id;
	typedef std::map<int ,double> map_id;
	std::list<pair_id> ml;
	pair_id id;
	id.first = 1;
	id.second=21.2;
	ml.push_back(id);
	map_id mid;
	mid[1]= 12.2;

	string srt;
	cout<<"please input full name\n";
	getline(cin,srt);
	cout<<srt<<endl;
	string srt2;
	cin>>srt2;
	
	cout<<srt+srt2;
}

#if 0
void main()
{
	// VectorTest();
	//ListTest();
	//ForEach();
	mtdd();
	system("pause");
	tr1::shared_ptr<int> mytr1;

	//HANDLE hMutex = CreateMutexW(NULL,false,"tickets");//�����������;
}
#endif