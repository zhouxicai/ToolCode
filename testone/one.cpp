#include <iostream>  
#include <Windows.h>  //需要引用Windows.h  
using namespace std;  


void OutColorText(char * cstring,unsigned short text_color,unsigned short back_color)
{
	HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,(text_color%16)|(back_color%16*16));
	cout<<cstring;  
	SetConsoleTextAttribute(hCon,(7%16)|(0%16*16));
}

void OutColorText2(char * cstring,char * color)
{
	char clor[64];
	sprintf(clor,"Color %s",color);
	system(clor);
	cout<<cstring;  
	system("Color 71");
}

#if 0
int main(int argc, char* argv[])  
{  
	cout<<"hello world.";
	OutColorText("I'm come ",50,0);
	//	OutColorText2("I'm come ","7b");
	cout<<"hello world.";

	system("TITLE BIAOTI");
	cin.get();  
	return 0;  
} 
#endif