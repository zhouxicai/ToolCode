#if 0
#if 0
C++ 模版元编程 笔记

	第二章 Traits和类型操纵 
	这一章主要让我们见识了用作类型计算的元编程，元编程可以在编译器操纵元数据，元数据分为类型(types)和非类型(non_types)。直接有iter_swap引入模版元编程的概念与意义，通过不断如的修改最终通过外覆器实现了一个兼顾了效率与正确性的版本，然后介绍了一下boost type_traits，发现2010中已经有类似的东西放到了了std下了，区别是考虑到C++0x的右值引用的引入，很多基本的元函数得加一些片特化。

	还是直接看代码比较帅气，下面是一些基本的类型操纵的元函数
	学SGI的做法先定义一个常量
#endif
#include <iostream>
using namespace std;

	template <class _Ty,_Ty _Val>
struct integral_constant {
	static const _Ty value=_Val;
	typedef _Ty value_type;
	typedef integral_constant<_Ty,_Val> type;
};

typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;

//看看判断两个型别是否相同的元函数;
	template <class _Ty,class _Tx>
struct is_same : false_type {
};

template <class _Ty>
struct is_same<_Ty,_Ty> : true_type {
};
//是否是引用的元函数;
	template <class _Ty>
struct is_reference : false_type {
};
template <class _Ty>
struct is_reference<_Ty &> : true_type {
};
//删除引用的元函数;
	template <class _Ty>
struct remove_reference {
	typedef _Ty type;
};
template <class _Ty>
struct remove_reference <_Ty&> {
	typedef _Ty type;
};
//看起来都挺简单;
//看一下第一个习题 编写一个元函数add_const_ref<T> 如果T是一个引用类型，范围T，否则返回 T const&;
	template <class _Ty>
struct add_const_ref {
	typedef _Ty const& type;
};
template <class _Ty> 
struct add_const_ref<_Ty&> {
	typedef _Ty& type;
};
//再看一个难点的,编写一个三元函数 replace_type<c,x,y> 它接受一个人一的符合类型c作为其第一个参数，并将c中出现的所有type x替换为y;
typedef replace_type<void*,void,int>::type t1;//int *;
typedef replace_type<int const*[10],int const,long>::type t2; // long*[10];
typedef replace_type<char&(*)(char&),char&,long&>::type t3;// long& (*) long(&);
//假定函数类型限制为最多两个参数 下面给出我的;
	template <class _Tc,class _Tx,class _Ty>
struct replace_type;

template <class _Tc,class _Tx,class _Ty,bool same>
struct replace_type_impl;

template <class _Tc,class _Tx,class _Ty>
struct replace_type_impl<_Tc,_Tx,_Ty,true> {
	typedef _Ty type;
};

template <class _Tc,class _Tx,class _Ty>
struct replace_type_impl<_Tc,_Tx,_Ty,false> {
	typedef _Tc type;
};

template <class _Tc,class _Tx,class _Ty>
struct replace_type_impl<_Tc*,_Tx,_Ty,false> {
	typedef typename replace_type<_Tc,_Tx,_Ty>::type * type;
};

template <class _Tc,class _Tx,class _Ty>
struct replace_type_impl<_Tc&,_Tx,_Ty,false> {
	typedef typename replace_type<_Tc,_Tx,_Ty>::type & type;
};

template <class _Tc,class _Tx,class _Ty>
struct replace_type_impl<_Tc[],_Tx,_Ty,false> {
	typedef typename replace_type<_Tc,_Tx,_Ty>::type type [];
};

template <class _Tc,class _Tx,class _Ty,int N>
struct replace_type_impl<_Tc[N],_Tx,_Ty,false> {
	typedef typename replace_type<_Tc,_Tx,_Ty>::type type [N];
};

template <class _Tc,class _Tx,class _Ty>
struct replace_type_impl<_Tc(),_Tx,_Ty,false> { //空;
	typedef    typename replace_type<_Tc,_Tx,_Ty>::type type();
};

template <class _Tc,class _Tx,class _Ty,class _Tb> //可以接受函数的引用;
struct replace_type_impl<_Tc(_Tb),_Tx,_Ty,false> { //1个参数;
	typedef typename replace_type<_Tc,_Tx,_Ty>::type type(typename replace_type<_Tb,_Tx,_Ty>::type);
};

template <class _Tc,class _Tx,class _Ty,class _Tb,class _Tbb>
struct replace_type_impl<_Tc(_Tb,_Tbb),_Tx,_Ty,false> {
	typedef typename replace_type<_Tc,_Tx,_Ty>::type type(typename replace_type<_Tb,_Tx,_Ty>::type,typename replace_type<_Tbb,_Tx,_Ty>::type);
};

template <class _Tc,class _Tx,class _Ty>
struct replace_type {
	static const bool same=is_same<_Tc,_Tx>::value;
	typedef typename replace_type_impl<_Tc,_Tx,_Ty,same>::type type;
};
//测试是否正确，可以用前面提到的is_same来检测;
std::cout << "exercise 2-1" << std::endl;
typedef replace_type<void*, void, int>::type t1;
std::cout << is_same<t1, int*>::value << std::endl;
typedef replace_type<int const*[10], int const, long>::type t2;    
std::cout << is_same<t2, long*[10]>::value << std::endl;
typedef replace_type<char&(&)(char&), char&, long&>::type t3;
std::cout << is_same<t3, long&(&)(long&)>::value << std::endl;
typedef replace_type<char&(*)(char&,char&), char&, long&>::type t4;
std::cout << is_same<t4, long&(*)(long&,long&)>::value << std::endl;

//再来看一个，实施一个type_descriptor类模版，当被流化时，打印模版参数类型;
	std::cout << type_descriptor<int>(); //int;
std::cout << type_descriptor<char*>(); //char*;
std::cout << type_descriptor<long const*&>();//long const*&;
//类型限制在int,short int,long int,char的复合类型，看实作;
	template <class _Ty>
struct type_descriptor {
	operator const char*() {
		return name.c_str();
	}
	static std::string name;
};
template <class _Ty>
std::string type_descriptor<_Ty>::name="unknow type";
template <>
std::string type_descriptor<int>::name="int";
template <>
std::string type_descriptor<short int>::name="short int";
template <>
std::string type_descriptor<char>::name="char";
template <>
std::string type_descriptor<long>::name="long";
template <class _Ty>
struct type_descriptor<_Ty&> {
	operator const char*() {
		static std::string ret=type_descriptor<_Ty>();
		ret += "&";
		return ret.c_str();
	}
};
template <class _Ty>
struct type_descriptor<_Ty*> {
	operator const char*() {
		static std::string ret=type_descriptor<_Ty>();
		ret += "*";
		return ret.c_str();
	}
};
template <class _Ty>
struct type_descriptor<_Ty const> {
	operator const char*() {
		static std::string ret=type_descriptor<_Ty>();
		ret += " const";
		return ret.c_str();
	}
};
template <class _Ty>
struct type_descriptor<_Ty volatile> {
	operator const char*() {
		static std::string ret=type_descriptor<_Ty>();
		ret += " volatile";
		return ret.c_str();
	}
};

#if 0
模版元编程在编译器，一般被称为"纯函数式语言"，因为其数据是不可变的，而且函数是没有副作用的，;
	正式由于这样，无法通过if等运行期的语句检查一些可变的东西的状态，所以递归是元编程的主要形式。
	有人说函数式语言就是 递归 ＋ 模式匹配 ，元编程里面，模式匹配当然就是利用模版的优先匹配规则，
	采用偏特化的手法实现的。

	最近看到csdn上的一个要求用最复杂的发放实现1+2+...+100的，我们用模版元来试试看。。。纯属娱乐
#endif



template <int n>
struct N {  //模版元;
	enum {value=N<n-1>::value+n};
};
template <>
struct N<1> {
	enum {value=1};
};

template <int n>
struct NN : public NN<n-1>{ //还利用运行期特性;
	NN() {NN::value+=n;}
};

template <> struct NN<1> {
	static int value;
	int getvalue() {return value;}
};
int NN<1>::value=1;



struct zero { //好吧，还是不爽，再来一个更刁的;
	enum {value=0};
};
struct one {
	enum {value=1};
};
template <int n> 
struct int_ { //编译器：我容易么？;
	enum {value=int_<n-1>::value+int_<1>::value}; 
	typedef int_<n> type;
};
template <>
struct int_<0> {
	enum {value=zero::value};
	typedef int_<0> type;
};
template <>
struct int_<1> {
	enum {value=one::value};
	typedef int_<1> type;
};

template <typename T>
struct next_ {
	typedef int_<T::value+int_<1>::value> type;
};
struct plus_ {
	template <typename S,typename T>
	struct apply: public int_<S::value+T::value> {
	};
};
/*
template <typename S,typename T,typename x,typename action>
struct for_ : public action::template apply<typename for_<typename next_<S>::type, T, x, action>::type, S> {
};
*/
template<typename S, typename T, typename x, typename action>
struct for_ : public for_<typename next_<S>::type, T, typename action::template apply<S, x>::type, action> {
};
template <typename T,typename x,typename action> 
struct for_<T,T,x,action> {
	typedef x type;
};

int main() {
	cout << N<100>::value << endl;
	cout << NN<100>().getvalue() << endl;
	cout << for_<int_<1>,int_<101>,int_<0>,plus_>::type::value << endl;
	return 0;
} 
#endif