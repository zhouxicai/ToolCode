#include <iostream>
#include <assert.h>

using namespace std;



//1.得分最低的
void strcpy1(char *dest, const char *src)
{
   while(*dest++ = *src++);
}
//2.好一点的
char * strcpy2(char *dest,const char *src)
{
    char * temp;
    temp = dest;
    while(*dest++ = *src++);
    return temp;
}
//3可以接受的
char * strcpy3(char *dest,const char *src)
{
     assert( dest != src);
     assert( dest != NULL || src != NULL);
     char *temp = dest;
     while(*dest++ = *src++);
     return temp;
}

char *strcpy4(char *strDest, const char *strSrc)
{
     assert( (strDest!=NULL)&&(strSrc !=NULL) ); 

     char *address = strDest; 
     while( (*strDest ++ = *strSrc ++) != '/0' ) NULL ;
     return address ; 
}

char * mystrcpy(char*dest,char*source)
{
	assert( dest!=NULL && source!=NULL && dest!=source );

	char * rstr = dest;
	while( *dest ++ = *source ++ );

	return rstr;
}

void main()
{
	char  ct1[6] ="hello";
	char * ct2 ="world";
	cout<<"strcmp(ct1,ct2):"<<strcmp(ct1,ct2)<<endl;
	cout<<"ct1:"<<ct1<<" ct2:"<<ct2<<endl;

	mystrcpy(ct1,ct2);
	cout<<"strcmp(ct1,ct2):"<<strcmp(ct1,ct2)<<endl;

	ct2 = "china";

	cout<<"ct1:"<<ct1<<" ct2:"<<ct2<<endl;
	

	system("pause");
}

