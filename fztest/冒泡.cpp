#include <stdio.h>
#include <stdlib.h>

//ð������, pnDataҪ��������ݣ� nLen���ݵĸ���;
int BubbleSort(int* pnData, int nLen)
{
	bool isOk = false;        //���������Ƿ�������ڱ�;

	//i��[0,nLen-1)��ʼð�ݣ�ȷ����i��Ԫ��;
	for (int i = 0; i < nLen - 1 && !isOk; ++i)
	{
		isOk = true;        //�ٶ�����ɹ�;

		//��[nLen - 1, i������Ƿ������һ��С����С��ð�ݸ���ȥ;
		for (int j = nLen- 1; j > i; --j)
		{
			if (pnData[j] < pnData[j - 1])    //�������ı�����С������;
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
	int nData[10] = {4,10,9,8,7,6,5,4,3,2};    //����10�����ݣ�����;
	BubbleSort(nData, 10);        //����ð������;

	for (int i = 0; i < 10; ++i)        
	{
		printf("%d ", nData[i]);
	}

	printf("\n");
	system("pause");
	return 0;
}
#endif