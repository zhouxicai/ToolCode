#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using namespace std;
using namespace boost;
using namespace tr1;
//effective c++ ����13:�ԣ�����ָ�룩���������Դ;
class resource
{
public:
	int GetOne()const{return one;}
	void SetOne(int one1){ one=one1;}
private:
	int one : 5;
	int		: 2;
};

class User
{
public:
	resource * CreateResource()
	{
		return res = new resource;
	}
	void SetResource(resource* re)
	{
		return re->SetOne(re->GetOne()+1);
	}
	void use()
	{

	}
private:
	resource * res;
};
User use;//��shared_ptr���������Դ;
std::tr1::shared_ptr<resource>pShar( use.CreateResource());
void Use()
{

	
	pShar->GetOne();
	cout<<pShar.use_count()<<endl;
	User use1;use1.SetResource(pShar.get());//get������ȡ�ڲ�ԭʼָ��;
	
	//�����ͷ�;
}
/*Ҳ����ʹ��auto_ptr����̬���󣬲���ֻ�ܹ���һ�����󣬶�����׳����⡣������shared_ptr���������󣬶��������󡣲��ҿ���ʹ�ñ�׼�����洢;
��Դ������ܰ�����������Կ���Դй¶�ı��ݡ��ų��˵�й¶���������ϵͳ�ĸ�����
����16����ס���Զ�����佫newed����洢������ָ���ڡ��������������һ����;�쳣���׳����п��ܵ������Բ������Դй¶;
����32��public�̳���ζ��is-a��������base classes���ϵ�ÿһ����һ��Ҳ������derived classes���ϣ���Ϊÿһ��derived class����Ҳ����һ��base class����;
*/
//int main()
//{
//	Use();
//	cout<<pShar.use_count()<<endl;
//	system("pause");
//}