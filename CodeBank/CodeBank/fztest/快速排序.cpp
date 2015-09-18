#include <stdio.h>
#include <stdlib.h>

//��������,�ҵ����Ԫ�ص�����λ�á������طָ��ĵ㣨�����һ���������λ�ã���;
//���ֵ�������[nBegin, nEnd). pData�Ǳ������ݵ�ָ��;
int Partition2EX(int* pData, int nBeging, int nEnd)
{
	int i = nBeging - 1;    //�ָ����ţ����nD����������;
	--nEnd;
	int nD = pData[nEnd]; //�Ƚϵ����ݡ�;
	int nTemp; // �����õ���ʱ����;

	//�������ݱȽϣ��ҵ�nD��λ�ã�����ע�⣬�ȽϽ����,;
	//���i�������С�ڵ���nD�ģ�i���ұ��Ǵ���nD��;
	for (int j = nBeging; j < nEnd; ++j)
	{
		if (pData[j] <= nD)        //������ݱ�Ҫ�Ƚϵ�С�����ڸ����ݵ���ߣ���i+1����;
		{
			++i;                //С��nD�����ݶ�һ��������Ҫ��1��i��������ݶ���nDС;
			nTemp = pData[i];    //��������;
			pData[i] = pData[j];
			pData[j] = nTemp;
		}
	}

	//���Ҫ���˰�nD��i+1��������Ϊ�������nD��λ�ÿ���;
	++i;
	pData[nEnd] = pData[i];
	pData[i] = nD;

	return i;   //����nD��λ�ã����Ƿָ��λ�á�;
}

//����ĵݹ���á�;
int QuickSortRecursion3ex(int* pData, int nBeging, int nEnd)
{
	if (nBeging >= nEnd -1)        //������򲻴��ڻ�ֻ��һ�������򲻵ݹ�����;
	{
		return 1;
	}

	//������Ϊ�ָ��ʱ�򣬷ָ�㴦�����ݾ�������������λ�á�;
	//Ҳ����˵������ߵ����ݶ�С�ڵ����������ұߵ����ݶ���������;
	//���������ڵݹ���õ������С�;
	int i = Partition2EX(pData, nBeging, nEnd);        //�ҵ��ָ��;
	QuickSortRecursion3ex(pData, nBeging, i);            //�ݹ���ߵ�����;
	QuickSortRecursion3ex(pData, i + 1, nEnd);            //�ݹ��ұߵ�����;
	return 1;
}

//��������;
int QuickSort(int* pData, int nLen)
{
	//�ݹ���ã���������;
	QuickSortRecursion3ex(pData, 0, nLen);
	return 1;
}
#if 0
int main()
{
	int nData[10] = {5,9,3,2,1,6,20,45,88,75};        //��������;
	QuickSort(nData, 10);            //���ÿ�������;
	for (int i = 0; i < 10; ++i)        //������;
	{
		printf("%d ", nData[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}
#endif