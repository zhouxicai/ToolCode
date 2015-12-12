#include <stdio.h>
#include <stdlib.h>

//冒泡排序, pnData要排序的数据， nLen数据的个数;
int BubbleSort(int* pnData, int nLen)
{
	bool isOk = false;        //设置排序是否结束的哨兵;

	//i从[0,nLen-1)开始冒泡，确定第i个元素;
	for (int i = 0; i < nLen - 1 && !isOk; ++i)
	{
		isOk = true;        //假定排序成功;

		//从[nLen - 1, i）检查是否比上面一个小，把小的冒泡浮上去;
		for (int j = nLen- 1; j > i; --j)
		{
			if (pnData[j] < pnData[j - 1])    //如果下面的比上面小，交换;
			{
				int nTemp = pnData[j];
				pnData[j] = pnData[j - 1];
				pnData[j - 1] = nTemp;
				isOk = false;
			}
		}
	}

	return 1;
}

#if 0
int main()
{
	int nData[10] = {4,10,9,8,7,6,5,4,3,2};    //创建10个数据，测试;
	BubbleSort(nData, 10);        //调用冒泡排序;

	for (int i = 0; i < 10; ++i)        
	{
		printf("%d ", nData[i]);
	}

	printf("\n");
	system("pause");
	return 0;
}
#endif