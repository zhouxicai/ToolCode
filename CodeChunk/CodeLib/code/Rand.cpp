// �����������
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <iostream>
using namespace std;


//    �������ĳ��Χ���������,����ǰ�ǵ�srand��������
int range_random(int start, int end)
{
    return    ( start + rand() % (end - start + 1) );
}

int main()
{
    float num;
    int i, length = 100;

    /* ���������ǰ������������srand()��ʼ���������������
     * ������time����ֵ������ǰʱ��,Ҳ������getpid()������rand()�ṩ����,
     * ���δ����������ӣ�rand()�ڵ���ʱ���Զ������������Ϊ1,
     * ������������������ͬ����Ϊrand�����������������α������еģ�
     */
    srand((unsigned)time(NULL)); 

    // ����ʮ��(0,length)֮��ĸ�����
    for(i = 0;i < length;i++)
    {
        // rand()�᷵��һ�����ֵ����Χ��0��RAND_MAX ��
        // RAND_MAX ��stdlib.h�ж��壬��ֵΪ0x7FFF ����һע��
        /* Maximum value that can be returned by the rand function. */
        num = length * ( rand() / (RAND_MAX+1.0) );
        cout << num << endl;
    }
    cout << endl;

    // ���Ҫ�������ĳ��Χ������
	length = 20;
	for(i = 0;i < length;i++){
		int rd = range_random(0, length);
		cout << rd << endl; 
	}
	system("pause");
    return 0;
}