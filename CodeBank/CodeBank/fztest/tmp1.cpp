#if 0
#if 0
C++ ģ��Ԫ��� �ʼ�

	�ڶ��� Traits�����Ͳ��� 
	��һ����Ҫ�����Ǽ�ʶ���������ͼ����Ԫ��̣�Ԫ��̿����ڱ���������Ԫ���ݣ�Ԫ���ݷ�Ϊ����(types)�ͷ�����(non_types)��ֱ����iter_swap����ģ��Ԫ��̵ĸ��������壬ͨ����������޸�����ͨ���⸲��ʵ����һ�������Ч������ȷ�Եİ汾��Ȼ�������һ��boost type_traits������2010���Ѿ������ƵĶ����ŵ�����std���ˣ������ǿ��ǵ�C++0x����ֵ���õ����룬�ܶ������Ԫ�����ü�һЩƬ�ػ���

	����ֱ�ӿ�����Ƚ�˧����������һЩ���������Ͳ��ݵ�Ԫ����
	ѧSGI�������ȶ���һ������
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

//�����ж������ͱ��Ƿ���ͬ��Ԫ����;
	template <class _Ty,class _Tx>
struct is_same : false_type {
};

template <class _Ty>
struct is_same<_Ty,_Ty> : true_type {
};
//�Ƿ������õ�Ԫ����;
	template <class _Ty>
struct is_reference : false_type {
};
template <class _Ty>
struct is_reference<_Ty &> : true_type {
};
//ɾ�����õ�Ԫ����;
	template <class _Ty>
struct remove_reference {
	typedef _Ty type;
};
template <class _Ty>
struct remove_reference <_Ty&> {
	typedef _Ty type;
};
//��������ͦ��;
//��һ�µ�һ��ϰ�� ��дһ��Ԫ����add_const_ref<T> ���T��һ���������ͣ���ΧT�����򷵻� T const&;
	template <class _Ty>
struct add_const_ref {
	typedef _Ty const& type;
};
template <class _Ty> 
struct add_const_ref<_Ty&> {
	typedef _Ty& type;
};
//�ٿ�һ���ѵ��,��дһ����Ԫ���� replace_type<c,x,y> ������һ����һ�ķ�������c��Ϊ���һ������������c�г��ֵ�����type x�滻Ϊy;
typedef replace_type<void*,void,int>::type t1;//int *;
typedef replace_type<int const*[10],int const,long>::type t2; // long*[10];
typedef replace_type<char&(*)(char&),char&,long&>::type t3;// long& (*) long(&);
//�ٶ�������������Ϊ����������� ��������ҵ�;
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
struct replace_type_impl<_Tc(),_Tx,_Ty,false> { //��;
	typedef    typename replace_type<_Tc,_Tx,_Ty>::type type();
};

template <class _Tc,class _Tx,class _Ty,class _Tb> //���Խ��ܺ���������;
struct replace_type_impl<_Tc(_Tb),_Tx,_Ty,false> { //1������;
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
//�����Ƿ���ȷ��������ǰ���ᵽ��is_same�����;
std::cout << "exercise 2-1" << std::endl;
typedef replace_type<void*, void, int>::type t1;
std::cout << is_same<t1, int*>::value << std::endl;
typedef replace_type<int const*[10], int const, long>::type t2;    
std::cout << is_same<t2, long*[10]>::value << std::endl;
typedef replace_type<char&(&)(char&), char&, long&>::type t3;
std::cout << is_same<t3, long&(&)(long&)>::value << std::endl;
typedef replace_type<char&(*)(char&,char&), char&, long&>::type t4;
std::cout << is_same<t4, long&(*)(long&,long&)>::value << std::endl;

//������һ����ʵʩһ��type_descriptor��ģ�棬��������ʱ����ӡģ���������;
	std::cout << type_descriptor<int>(); //int;
std::cout << type_descriptor<char*>(); //char*;
std::cout << type_descriptor<long const*&>();//long const*&;
//����������int,short int,long int,char�ĸ������ͣ���ʵ��;
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
ģ��Ԫ����ڱ�������һ�㱻��Ϊ"������ʽ����"����Ϊ�������ǲ��ɱ�ģ����Һ�����û�и����õģ�;
	��ʽ�����������޷�ͨ��if�������ڵ������һЩ�ɱ�Ķ�����״̬�����Եݹ���Ԫ��̵���Ҫ��ʽ��
	����˵����ʽ���Ծ��� �ݹ� �� ģʽƥ�� ��Ԫ������棬ģʽƥ�䵱Ȼ��������ģ�������ƥ�����
	����ƫ�ػ����ַ�ʵ�ֵġ�

	�������csdn�ϵ�һ��Ҫ������ӵķ���ʵ��1+2+...+100�ģ�������ģ��Ԫ�����Կ���������������
#endif



template <int n>
struct N {  //ģ��Ԫ;
	enum {value=N<n-1>::value+n};
};
template <>
struct N<1> {
	enum {value=1};
};

template <int n>
struct NN : public NN<n-1>{ //����������������;
	NN() {NN::value+=n;}
};

template <> struct NN<1> {
	static int value;
	int getvalue() {return value;}
};
int NN<1>::value=1;



struct zero { //�ðɣ����ǲ�ˬ������һ�������;
	enum {value=0};
};
struct one {
	enum {value=1};
};
template <int n> 
struct int_ { //��������������ô��;
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