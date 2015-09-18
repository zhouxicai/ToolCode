#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <hash_map>
#include <bitset>
#include <unordered_map>
#include <assert.h>
using namespace std;

void unordered_map()
{
	tr1::unordered_map<string,string> mymap;


	mymap["house"] = "maison";
	mymap["apple"] = "pomme";
	mymap["tree"] = "arbre";
	mymap["book"] = "livre";
	mymap["door"] = "porte";
	mymap["grapefruit"] = "pamplemousse";


	tr1::unordered_map<string,string> unmap;

	unmap["us"] = "United States";
	unmap["uk"] = "United Kingdom";

	pair<string,string> mp;
	mp.first  = "cn";
	mp.second = "china";
	unmap.insert(mp);    



	tr1::unordered_map<string,string>::iterator umt;

	for(umt = unmap.begin(); umt!=unmap.end();umt++)
	{
		cout<< umt->first<<" = "<<umt->second<<endl;
		cout<<"at bucket:"<<unmap.bucket(umt->second)<<endl;
	}	
}
void mymap()
{
	map<string,string> mymap;
	mymap["sd"] = "jeep";

	map<int,string> map1;
	map1[0] = "boat";
	map1[1] = "ship";

	cout<<"mymap sd = "<<mymap["sd"]<<endl;

	for(unsigned int i=0;i<map1.size();++i)
		cout<<"map1 = "<<map1[i]<<endl;
}
//void main()
//{
//	system("pause");
//}

