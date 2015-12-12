#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"


using namespace boost;
class A {};

void testptr()
{
	weak_ptr<A> p_wk;
	assert(p_wk.expired());
	{
		boost::shared_ptr<A> p_sh(new A());
		assert(p_sh.use_count()==1);
		p_wk=p_sh;
		assert(p_sh.use_count()==p_wk.use_count());
		assert(p_sh.use_count()==1);

		// ´Óweak_ptr´´½¨shared_ptr 
		boost::shared_ptr<A> p_wk2(p_wk);
		assert(p_wk2==p_sh);
	}
	assert(p_wk.expired());
	boost::shared_ptr<A> p_sh2=p_wk.lock();
	assert(!p_sh2);
}
template <typename Func, typename T> 
struct weak_ptr_unary_t : 
	public std::unary_function<boost::weak_ptr<T>,bool> {
		T t_;
		Func func_;

		weak_ptr_unary_t(const Func& func,const T& t) 
			: t_(t),func_(func) {}

		bool operator()(boost::weak_ptr<T> arg) const {
			boost::shared_ptr<T> sp=arg.lock();
			if (!sp) {
				return false;
			}
			return func_(*sp,t_);
		}
};

//
//int main() 
//{
//
//	testptr();
//
//	system("pause");
//}