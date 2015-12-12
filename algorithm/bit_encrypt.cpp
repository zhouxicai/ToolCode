
#include "bit_encrypt.h"

int bit()
{
	int key[8] ={6,2,3,4,5};//{'a','b','c','d','e'};//{0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
	int source[8] ={80,70,60,50,-40};//{'e','f','g','h','i'};//{0xef,0x7a,0x8d,0x9c,0x34,0x57,0xf2,0xd8};
	int result[8];
 
	for(int i = 0;i<5;i++)
	{
		cout<<"source:"<<source[i]<<endl;
		result[i] = source[i]<<key[i];
		cout<<"encrypt:"<<result[i]<<endl;
	}
	cout<<"-----"<<endl;
	for(int i = 0;i<5;i++)
	{
		result[i] = result[i]>>key[i];
		cout<<"decrypt:"<<result[i]<<endl;
	}
	return 0;
}
