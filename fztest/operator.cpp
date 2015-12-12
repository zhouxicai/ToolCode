#include <iostream>
#include <Windows.h>
void and()
{
	bool a = 1;
	bool b = 1;
	bool c=1;
	if (c &
		a++)
	{
		a++;
	}
	else
	{
		b++;
	}
	if (c &&
		a++)
	{
		a++;
	}
	else
	{
		b++;
	}


}
void ts()
{
	int a=16;
	int b=16;
	int c=16;
	if (a==b&&b==c)
	{
		std::cout<<"suc!";
	} 
	else
	{
		std::cout<<"fal!";
	}
}
#if 0
void main()
{ts();system("pause");}
#endif