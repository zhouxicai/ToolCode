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
	//a&b �����㣬�᷵��a��b�У�ÿ��λ�����أ��������ƣ���С��ֵ;	
	value	=	1&1;	   //1
	value	=	1&0;	   //0
	value	=	0&1;	   //0
	value	=	0&0;	   //0

	value	=	3&3;	   //3 �����Ƽ��㣺11=11&11
	value	=	3&2;	   //2 �����Ƽ��㣺10=11&10
	value	=	2&3;	   //2 �����Ƽ��㣺10=10&11
	value	=	5&6;	   //4 �����Ƽ��㣺100=101&110
	value	=	213&73;	   //65

	//a|b �����㣬�᷵��a��b�У�ÿ��λ�����أ�����ֵ;	
	value	=	1|1;	   //1
	value	=	1|0;	   //1
	value	=	0|1;	   //1
	value	=	0|0;	   //0

	value	=	3|3;	   //3 �����Ƽ��㣺11=11 | 11
	value	=	3|2;	   //3 �����Ƽ��㣺11=11 | 10
	value	=	2|3;	   //3 �����Ƽ��㣺11=10 | 11
	value	=	5|6;	   //7 �����Ƽ��㣺111=101 | 110
	value	=	213|73;	   //221

	//a^b �����㣬�᷵��a��b�У�ÿ��λ�����أ��Ƿ�ͬ��(���)boolֵ����ͬ1����ͬ0��;	
	value	=	1^1;	   //0 �����Ƽ��㣺0=1^1
	value	=	1^0;	   //1 �����Ƽ��㣺1=1^0
	value	=	0^1;	   //1 �����Ƽ��㣺1=0^1
	value	=	0^0;	   //0 �����Ƽ��㣺0=0^0
	value	=	5^6;	   //3 �����Ƽ��㣺011=101^110
	value	=	213^73;	   //156

	//~��λȡ�����㣬~�ǵ�Ŀ��������书���ǽ��������еĶ�����λ0���1��1���0;
	value	=	~0;		   //-1		�����Ƽ��㣺0		> -1	��-1
	value	=	~1;		   //-2		�����Ƽ��㣺1		> -10	��-2
	value	=	~2;		   //-3		�����Ƽ��㣺10		> -01
	value	=	~3;		   //-4
	value	=	~4;		   //-5
	value	=	~5;		   //-6
	value	=	~-7;		//6
	value	=	~100;	   //-101

	// �������� �����������<<����˫Ŀ��������书�ܰѡ�<< ����ߵ��������ĸ�����λȫ����������λ���ɡ�<<���ұߵ���ָ���ƶ���λ����
	// ��λ��������λ��0�����磺 a<<4 ָ��a�ĸ�����λ�����ƶ�4λ����a=00000011(ʮ����3)������4λ��Ϊ00110000(ʮ����48)��
	// �������������������>>����˫Ŀ��������书���ǰѡ�>> ����ߵ��������ĸ�����λȫ����������λ����>>���ұߵ���ָ���ƶ���λ����
	// ���磺�� a=15��a>>2 ��ʾ��000001111����Ϊ00000011(ʮ����3)��Ӧ��˵�����ǣ������з�������������ʱ������λ����ͬ�ƶ���
	// ��Ϊ����ʱ�� ���λ��0����Ϊ����ʱ������λΪ1�����λ�ǲ�0���ǲ�1 ȡ���ڱ���ϵͳ�Ĺ涨��Turbo C�ͺܶ�ϵͳ�涨Ϊ��1��
	// 0 1 10 11 100 101 110 111 1000 1001
	value	=	1<<0;		//1		�����Ƽ��㣺01 ���ƶ�0λ���� 1
	value	=	1<<1;		//2		�����Ƽ��㣺01 ���ƶ�1λ�� 10	 �� 2
	value	=	1<<2;		//4		�����Ƽ��㣺01 ���ƶ�2λ�� 100	 �� 4
	value	=	1<<3;		//8		�����Ƽ��㣺01 ���ƶ�3λ�� 1000	 �� 8
	value	=	1<<4;		//16	�����Ƽ��㣺01 ���ƶ�3λ�� 10000 �� 16
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
	HWND hWnd=FindWindowA(NULL,argv[0]); //�ҵ��������д��ڵľ��;       
	HDC hDC=GetDC(hWnd);//ͨ�����ھ���õ��ô��ڵ��豸�������;        
	//HPEN hPen; //����;       	         
	//       
	//hPen=CreatePen(PS_DASH,2,0x00ff00);//������ɫ����;         
	//SelectObject(hDC,hPen);//�ѻ��������豸���� ;   
	//Arc(hDC,100,100,300,300,350,500,350,500);//��Բ ; 
	//SelectObject(hDC,hPen);//��ԭ ;  

	//for(int i=0;i<500;++i)            
	//	SetPixel(hDC,10+i,10+i,0x0000ff);//�û���İ취��һ����,���һ����������ɫ��32λ��; 
	//	MoveToEx(hDC,20,50,NULL); //���û������;        
	//	LineTo(hDC,520,550);      //�����յ�;         	       

	system("pause");      
	return 0; 

} 
#endif