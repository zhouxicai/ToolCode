#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using namespace std;
using namespace boost;
using namespace tr1;
//effective c++ 条款13:以（智能指针）对象管理资源;
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
User use;//以shared_ptr对象管理资源;
std::tr1::shared_ptr<resource>pShar( use.CreateResource());
void Use()
{

	
	pShar->GetOne();
	cout<<pShar.use_count()<<endl;
	User use1;use1.SetResource(pShar.get());//get方法获取内部原始指针;
	
	//智能释放;
}
/*也可以使用auto_ptr管理动态对象，不过只能管理一个对象，多个容易出问题。可以用shared_ptr管理多个对象，而不出错误。并且可以使用标准容器存储;
资源管理类很棒。它们是你对抗资源泄露的堡垒。排除此等泄露是良好设计系统的根本。
条款16：记住，以独立语句将newed对象存储于智能指针内。如果不这样做，一旦中途异常被抛出，有可能导致难以察觉的资源泄露;
条款32：public继承意味着is-a。适用于base classes身上的每一件事一定也适用于derived classes身上，因为每一个derived class对象也都是一个base class对象;
*/
//int main()
//{
//	Use();
//	cout<<pShar.use_count()<<endl;
//	system("pause");
//}