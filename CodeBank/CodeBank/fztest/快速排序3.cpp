#include <stdio.h>
#include <stdlib.h>

//化分区间,找到最后元素的排序位置。并返回分隔的点（即最后一数据排序的位置）。;
//划分的区间是[nBegin, nEnd). pData是保存数据的指针;
int PartitionEX(int* pData, int nBeging, int nEnd)
{
	//这里是和hoare的最初快速排序的版本。;
	int x = pData[nBeging];
	--nBeging;

	while (nBeging < nEnd)
	{
		--nEnd;
		//从后向前，找到比X小的元素位置;
		while(pData[nEnd] > x)
		{
			--nEnd;
		}

		//小的区域增加，找到一个不比x小的元素;
		++nBeging;
		while (pData[nBeging] < x)
		{
			++nBeging;
		}

		//把不比x小的元素存放在大的区域内。nEnd刚好预留了此位置。;
		if (nBeging < nEnd)
		{
			int nTemp = pData[nBeging];
			pData[nBeging] = pData[nEnd];
			pData[nEnd] = nTemp;
		}
		else
		{
			break;
		}
	}

	//注意这里并没有给分割点排序，只是做了分割，办证nEnd+1的左边小于;
	//nEnd + 1的右边。;
	return nEnd + 1;   //返回nD的位置，就是分割的位置。;
}

//排序的递归调用。;
int QuickSortRecursion2ex(int* pData, int nBeging, int nEnd)
{
	if (nBeging >= nEnd -1)        //如果区域不存在或只有一个数据则不递归排序;
	{
		return 1;
	}

	//也就是说他的左边的数据都小于等于他，他右边的数据都大于他。;
	//所以他不在递归调用的数据中。;
	int i = PartitionEX(pData, nBeging, nEnd);        //找到分割点;
	QuickSortRecursion2ex(pData, nBeging, i);            //递归左边的排序;
	QuickSortRecursion2ex(pData, i, nEnd);            //递归右边的排序;
	return 1;
}

//快速排序;
int QuickSort2(int* pData, int nLen)
{
	//递归调用，快速排序。;
	QuickSortRecursion2ex(pData, 0, nLen);
	return 1;
}
#if 0
int main()
{
	int nData[10] = {5,9,3,2,1,6,20,45,88,75};        //测试数据;
	QuickSort2(nData, 10);            //调用快速排序;
	for (int i = 0; i < 10; ++i)        //输出结果;
	{
		printf("%d ", nData[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}
#endif