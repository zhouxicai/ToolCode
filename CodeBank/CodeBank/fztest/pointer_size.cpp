#include <iostream>

using namespace std;

void ptrfun(const char * const pt)
{
	cout<<"ptrfun"<<endl
		<<"pt:"<<pt<<endl
		<<"*pt:"<<*pt<<endl
		<<"&pt:"<<&pt<<endl;
	const char * x = pt;
}

void point_size()
{
	int i = 3;
	int * ip = &i;
	cout<<"&i:"<<&i<<" ip:"<<ip<<" &ip:"<<&ip<<" *ip:"<<*ip<<endl;

	int j = 8;
	int *ip2 = &j;

	cout<<"&ip2-&ip:"<<(&ip2-&ip)<<" ip2-ip:"<<(ip2-ip)<<" *ip2-*ip:"<<(*ip2-*ip)<<endl;


	char * c ="china";
	cout<<"&c:"<<&c<<" *c"<<*c<<" "<<&"china"<<endl;
	ptrfun(c);
}