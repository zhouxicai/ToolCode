#include <iostream>  
#include<stdio.h>
#include<string.h>
#include <Windows.h>  //需要引用Windows.h  
using namespace std;  




void main()
{
	int dwGuideInfo[10];

	
		char test1[] = "feng,ke,wei,gb,tt,iy,rt,i,ui";  
		char *test2 = "feng,ke,wei";  

		char *p;  
		p = strtok(test1, ",");
		while(p)  
		{   
			printf("%s\n", p);   
			p = strtok(NULL, ",");     
		}    




	system("pause");
}