#include <direct.h>
#include <time.h>  
#include"common.h"
//#include"TimeCount.h"

const int MAX = 54;
int nCard[MAX];
char *s16[MAX]={
	"0x01","0x02","0x03","0x04","0x05","0x06","0x07","0x08","0x09","0x0A","0x0B","0x0C","0x0D",
	"0x11","0x12","0x13","0x14","0x15","0x16","0x17","0x18","0x19","0x1A","0x1B","0x1C","0x1D",
	"0x21","0x22","0x23","0x24","0x25","0x26","0x27","0x28","0x29","0x2A","0x2B","0x2C","0x2D",
	"0x31","0x32","0x33","0x34","0x35","0x36","0x37","0x38","0x39","0x3A","0x3B","0x3C","0x3D","0x4E","0x4F" };

int xipai(int index = 0)
{
	srand(time(0));
    for(int i=0; i<MAX; i++)
    {
        nCard[i] = i + 1;
    }
    random_shuffle(nCard, nCard+MAX);
    //for(int i=0; i<MAX; i++)
    //{
    //    cout << nCard[i] << endl;
    //}
    return nCard[index]-1;
}

void convert()
{
    
    
    int a,c;
	int min = 1;
	int max = 2;
	cout <<"请输入[起始]文件编号："<<endl;
	cin >>min;
	cout <<"请输入[结束]文件编号："<<endl;
	cin >>max;
	
	//time_t now_time;
	//now_time = time(NULL);
	//cout<<now_time<<endl;



	// 用时间创建目录
	char dir[64];

	//struct tm *local;   
	//time_t t;   
	//t=time(0);    
	//local=localtime(&t); 
//	sprintf(dir,"%d_%d_%d_%d_%d_%d",local->tm_year,local->tm_mon,local->tm_mday,local->tm_hour,local->tm_sec,local->tm_min);
	
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	sprintf(dir,"%d_%d_%d_%d_%d_%d_%d",sys.wYear ,sys.wMonth ,sys.wDay ,sys.wHour ,sys.wSecond ,sys.wMinute ,sys.wMilliseconds);
	_mkdir(dir);
	
	for(c=min;c<=max;c++)
	{
		ofstream out;
		char buffer [256] ;
		strcpy(buffer,dir);
		char buffer2 [128] ;
		sprintf(buffer2,"/moto%d.ini",c);
		strcat(buffer,buffer2);
		cout <<"buffer："<<buffer<<endl;
		out.open(buffer);

		//timeCount.InitTime();
		for(int w=1;w<=200;w++)    
		{
			
			out<<"[Table"<<w<<"]"<<endl; 
			//srand(timeCount.GetNowTime());
			Sleep(0);
			for(a=1;a<=54;a++)    
			{
				//srand(time(0));
				//Sleep(1);
				int x = xipai(a-1);
				//cout << x <<",";
				out<<"readBuffer"<<a<<"="<<s16[x]<<endl;    //输出16进制
			}
		}
		out.close();
	}
          
}

const int POKER_NUM = 54; //52张扑克牌

void print_poker(int PokerNum)
{
    //cout << PokerNum << " ";
}

class MyRand
{    
public:
    int operator()(int index)
    {
        return rand() % POKER_NUM;
    }
};

int xipai_test()
{
	int a,c;
	int min = 1;
	int max = 2;
	cout <<"请输入[起始]文件编号："<<endl;
	cin >>min;
	cout <<"请输入[结束]文件编号："<<endl;
	cin >>max;

	// 用时间创建目录
	char dir[64];	
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	sprintf(dir,"%d_%d_%d_%d_%d_%d_%d",sys.wYear ,sys.wMonth ,sys.wDay ,sys.wHour ,sys.wSecond ,sys.wMinute ,sys.wMilliseconds);
	_mkdir(dir);


    srand( (unsigned)time(NULL) ); //设置随即数生成器的种子
    vector<int> poker; //一副牌,牌点数从 1 计
	
	for(c=min;c<=max;c++)
	{
		ofstream out;
		char buffer [256] ;
		strcpy(buffer,dir);
		char buffer2 [128] ;
		sprintf(buffer2,"/moto%d.ini",c);
		strcat(buffer,buffer2);
		cout <<"buffer："<<buffer<<endl;
		out.open(buffer);


		//初始化
		for (int num = 0; num < POKER_NUM; num++)
		{
			poker.push_back(num+1);
		}
		for (int w = 0; w < 200; w++)
		{
			out<<"[Table"<<w<<"]"<<endl; 
			//用默认随机数洗一遍
			random_shuffle(poker.begin(), poker.end());
			//for_each(poker.begin(), poker.end(), print_poker);
			//cout << endl;

			//用自定义随机数再洗一遍
			random_shuffle(poker.begin(), poker.end(), MyRand());
			//copy(poker.begin(), poker.end(), ostream_iterator<int>(cout, " "));
			//cout << endl<< endl;    

				for (int num = 0; num < POKER_NUM; num++)
				{
					int idx =poker.at(num);
					if (idx && idx >= 0 && idx < 54)
					out<<"readBuffer"<<num+1<<"="<<s16[idx-1]<<endl;    //输出16进制
				}
			
		}
		out.close();
	}
	return 1;
}


