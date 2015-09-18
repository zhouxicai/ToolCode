#include <stdio.h>
#include <stdlib.h>

//��������,�ҵ����Ԫ�ص�����λ�á������طָ��ĵ㣨�����һ���������λ�ã���;
//���ֵ�������[nBegin, nEnd). pData�Ǳ������ݵ�ָ��;
int PartitionEX(int* pData, int nBeging, int nEnd)
{
	//�����Ǻ�hoare�������������İ汾��;
	int x = pData[nBeging];
	--nBeging;

	while (nBeging < nEnd)
	{
		--nEnd;
		//�Ӻ���ǰ���ҵ���XС��Ԫ��λ��;
		while(pData[nEnd] > x)
		{
			--nEnd;
		}

		//С���������ӣ��ҵ�һ������xС��Ԫ��;
		++nBeging;
		while (pData[nBeging] < x)
		{
			++nBeging;
		}

		//�Ѳ���xС��Ԫ�ش���ڴ�������ڡ�nEnd�պ�Ԥ���˴�λ�á�;
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

	//ע�����ﲢû�и��ָ������ֻ�����˷ָ��֤nEnd+1�����С��;
	//nEnd + 1���ұߡ�;
	return nEnd + 1;   //����nD��λ�ã����Ƿָ��λ�á�;
}

//����ĵݹ���á�;
int QuickSortRecursion2ex(int* pData, int nBeging, int nEnd)
{
	if (nBeging >= nEnd -1)        //������򲻴��ڻ�ֻ��һ�������򲻵ݹ�����;
	{
		return 1;
	}

	//Ҳ����˵������ߵ����ݶ�С�ڵ����������ұߵ����ݶ���������;
	//���������ڵݹ���õ������С�;
	int i = PartitionEX(pData, nBeging, nEnd);        //�ҵ��ָ��;
	QuickSortRecursion2ex(pData, nBeging, i);            //�ݹ���ߵ�����;
	QuickSortRecursion2ex(pData, i, nEnd);            //�ݹ��ұߵ�����;
	return 1;
}

//��������;
int QuickSort2(int* pData, int nLen)
{
	//�ݹ���ã���������;
	QuickSortRecursion2ex(pData, 0, nLen);
	return 1;
}
#if 0
int main()
{
	int nData[10] = {5,9,3,2,1,6,20,45,88,75};        //��������;
	QuickSort2(nData, 10);            //���ÿ�������;
	for (int i = 0; i < 10; ++i)        //������;
	{
		printf("%d ", nData[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}
#endif