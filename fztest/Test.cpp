#include<Windows.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <memory.h>
//using namespace std;

struct count {
	int x1;
	int x2;
	int x3;
	int x4;
	int x5;
	int x6;
} c,*p;
void	test1()
{
		p=&c;
		__asm 
		{
			push ecx
				push edi
				mov eax,3
				mov ecx,6
				mov edi,p
				rep stosd
				pop edi
				pop ecx
		}
		printf("%d,%d,%d,%d,%d,%d\n",c.x1,c.x2,c.x3,c.x4,c.x5,c.x6);
		c.x1 = 1;
		c.x2 = 2;
		c.x3 = 3;
		c.x4 = 4;
		c.x5 = 5;
		c.x6 = 6;
		__asm 
		{
			push ecx
				push edi
				push esi
				mov esi,p
				mov edi,esi
				mov ecx,6
			next:
				lodsd
				neg eax
				stosd
				loop next
				pop esi
				pop edi
				pop ecx
		}
		printf("%d,%d,%d,%d,%d,%d\n",c.x1,c.x2,c.x3,c.x4,c.x5,c.x6);
	//3,3,3,3,3,3
	//-3,-3,-3,-3,-3,-3
}
void test3()
{
	int va = 3032%1000;
	va = 3032/1000;

	int 
	//a&b 的运算，会返回a和b中，每个位（比特，即二进制）最小的值;	
	value	=	1&1;	   //1
	value	=	1&0;	   //0
	value	=	0&1;	   //0
	value	=	0&0;	   //0

	value	=	3&3;	   //3 二进制计算：11=11&11
	value	=	3&2;	   //2 二进制计算：10=11&10
	value	=	2&3;	   //2 二进制计算：10=10&11
	value	=	5&6;	   //4 二进制计算：100=101&110
	value	=	213&73;	   //65

	//a|b 的运算，会返回a和b中，每个位（比特）最大的值;	
	value	=	1|1;	   //1
	value	=	1|0;	   //1
	value	=	0|1;	   //1
	value	=	0|0;	   //0

	value	=	3|3;	   //3 二进制计算：11=11 | 11
	value	=	3|2;	   //3 二进制计算：11=11 | 10
	value	=	2|3;	   //3 二进制计算：11=10 | 11
	value	=	5|6;	   //7 二进制计算：111=101 | 110
	value	=	213|73;	   //221

	//a^b 的运算，会返回a和b中，每个位（比特）是否不同的(真假)bool值（不同1，相同0）;	
	value	=	1^1;	   //0 二进制计算：0=1^1
	value	=	1^0;	   //1 二进制计算：1=1^0
	value	=	0^1;	   //1 二进制计算：1=0^1
	value	=	0^0;	   //0 二进制计算：0=0^0
	value	=	5^6;	   //3 二进制计算：011=101^110
	value	=	213^73;	   //156

	//~按位取反运算，~是单目运算符。其功能是将操作数中的二进制位0变成1，1变成0;
	value	=	~0;		   //-1		二进制计算：0		> -1	即-1
	value	=	~1;		   //-2		二进制计算：1		> -10	即-2
	value	=	~2;		   //-3		二进制计算：10		> -01
	value	=	~3;		   //-4
	value	=	~4;		   //-5
	value	=	~5;		   //-6
	value	=	~-7;		//6
	value	=	~100;	   //-101

	// 左移运算 左移运算符“<<”是双目运算符。其功能把“<< ”左边的运算数的各二进位全部左移若干位，由“<<”右边的数指定移动的位数，
	// 高位丢弃，低位补0。例如： a<<4 指把a的各二进位向左移动4位。如a=00000011(十进制3)，左移4位后为00110000(十进制48)。
	// 右移运算右移运算符“>>”是双目运算符。其功能是把“>> ”左边的运算数的各二进位全部右移若干位，“>>”右边的数指定移动的位数。
	// 例如：设 a=15，a>>2 表示把000001111右移为00000011(十进制3)。应该说明的是，对于有符号数，在右移时，符号位将随同移动。
	// 当为正数时， 最高位补0，而为负数时，符号位为1，最高位是补0或是补1 取决于编译系统的规定。Turbo C和很多系统规定为补1。
	// 0 1 10 11 100 101 110 111 1000 1001
	value	=	1<<0;		//1		二进制计算：01 左移动0位还是 1
	value	=	1<<1;		//2		二进制计算：01 左移动1位是 10	 即 2
	value	=	1<<2;		//4		二进制计算：01 左移动2位是 100	 即 4
	value	=	1<<3;		//8		二进制计算：01 左移动3位是 1000	 即 8
	value	=	1<<4;		//16	二进制计算：01 左移动3位是 10000 即 16
	value	=	1<<5;		//32
	value	=	1<<6;		//64
	value	=   1<<7;		//128
	value	=   1<<8;		//256
	value	=	1<<9;		//512

	value	=	512>>0;		//512	
	value	=	512>>1;		//256
	value	=	512>>2;		//128
	value	=	512>>3;		//64	
	value	=	512>>4;		//32
	value	=	512>>5;		//16
	value	=	512>>6;		//8
	value	=   512>>7;		//4
	value	=   512>>8;		//2
	value	=	512>>9;		//1

	int ax = 16 & 32;
		ax = 32 & 32;
		ax = 64 & 32;
		ax = 128 & 32;
		ax = 192 & 32;
		ax = 256 & 32;
		ax = 512 & 32;
		ax = 130 & 32;
		ax = 199 & 32;
		ax = 16 & 32;
	bool ab = 192 & 32;
	value &=29;

}

void test1x()
{
	int x = 33093/10;//%(1*100);
	x = 2*3 + 5*8 + 3*3;
	printf("x:%d",x);
}

#include <vector>
void test_vector()
{
	typedef std::vector<int> mv;	
	std::vector<mv> myv2;
	mv data,data2;
	data.push_back(1);
	data.push_back(2);
	data2.push_back(11);
	data2.push_back(22);
	myv2.push_back(data);
	myv2.push_back(data2);
	int 
	dresult = myv2.at(0).at(0);
	dresult = myv2.at(0).at(1);
	dresult = myv2.at(1).at(0);
	dresult = myv2.at(1).at(1);

}

#include <iostream>
#include <fstream>
#include <sstream> 
typedef std::vector<int> DATA;
typedef std::vector<DATA> TwoData;
void Display (TwoData const& t)
{   
	for (size_t i = 0; i < t.size(); ++i)   
	{      
		for (size_t j = 0; j < t[i].size(); ++j)      
		{         
			std::cout << t[i][j] << " ";      
		}     
		std::cout << std::endl;   
	}
}
void read_data()
{
	   TwoData td;  
	   std::ifstream     ifs("a.txt"); 

	   if (!ifs)   
	   {      
		   std::cerr << "open a.txt failed" << std::endl;      
		   return ;   
	   }    
	   std::string s;      
	   while (getline(ifs, s))   
	   {      
		   std::istringstream is(s);     
		   DATA  dt;
		   int    t;   
			while (is >> t)      	
			{         
				dt.push_back(t);      
			}      
			td.push_back(dt);  
	   }  
	   
	   ifs.close();    
	   Display(td);    
	   std::cin.get();
}


//using namespace std;
//void main()
//{
////	test_quick_sort();
////	test3();
//	//test1();
//	//test_vector();
//	DrawRoundness(9,6);
//
//	std::system("pause");
//	int x1 = 63 % 10;
//	 x1 = 2 / 10;
//	  x1 = 70 % 10;
////	while(1);
//	std::system("pause");
//}

#if 0
int main(int argc, char* argv[])
{         
	HWND hWnd=FindWindowA(NULL,argv[0]); //找到程序运行窗口的句柄;       
	HDC hDC=GetDC(hWnd);//通过窗口句柄得到该窗口的设备场境句柄;        
	//HPEN hPen; //画笔;       	         
	//       
	//hPen=CreatePen(PS_DASH,2,0x00ff00);//生成绿色画笔;         
	//SelectObject(hDC,hPen);//把画笔引入设备场境 ;   
	//Arc(hDC,100,100,300,300,350,500,350,500);//画圆 ; 
	//SelectObject(hDC,hPen);//复原 ;  

	//for(int i=0;i<500;++i)            
	//	SetPixel(hDC,10+i,10+i,0x0000ff);//用画点的办法画一根线,最后一个参数是颜色（32位）; 
	//	MoveToEx(hDC,20,50,NULL); //设置画线起点;        
	//	LineTo(hDC,520,550);      //画到终点;         	       

	system("pause");      
	return 0; 

} 
#endif