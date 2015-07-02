// 随机数的生成
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <iostream>
using namespace std;


//    随机生成某范围的随机整数,调用前记得srand设置种子
int range_random(int start, int end)
{
    return    ( start + rand() % (end - start + 1) );
}

int main()
{
    float num;
    int i, length = 100;

    /* 产生随机数前，必须先利用srand()初始化随机数发生器，
     * 这样以time函数值（即当前时间,也可以用getpid()），给rand()提供种子,
     * 如果未设随机数种子，rand()在调用时会自动设随机数种子为1,
     * 多次运行所得随机数相同（因为rand根据随机数种子生成伪随机序列的）
     */
    srand((unsigned)time(NULL)); 

    // 生成十个(0,length)之间的浮点数
    for(i = 0;i < length;i++)
    {
        // rand()会返回一随机数值，范围在0至RAND_MAX 间
        // RAND_MAX 在stdlib.h中定义，其值为0x7FFF ，有一注释
        /* Maximum value that can be returned by the rand function. */
        num = length * ( rand() / (RAND_MAX+1.0) );
        cout << num << endl;
    }
    cout << endl;

    // 如果要随机生成某范围的整数
	length = 20;
	for(i = 0;i < length;i++){
		int rd = range_random(0, length);
		cout << rd << endl; 
	}
	system("pause");
    return 0;
}