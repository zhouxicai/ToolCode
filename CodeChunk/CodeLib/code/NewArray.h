//C�����ж�̬�������ά���� malloc free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//��̬�����ά����
template <typename T>
T** malloc_Array2D(int row, int col)
{
	int size = sizeof(T);
	int point_size = sizeof(T*);
	//�������ڴ棬����point_size * row��ʾ���row����ָ��
	T **arr = (T **) malloc(point_size * row + size * row * col);
	if (arr != NULL)
	{	
		memset(arr, 0, point_size * row + size * row * col);
		T *head = (T*)((int)arr + point_size * row);
		while (row--)
			arr[row] = (T*)((int)head + row * col * size);
	}
	return (T**)arr;
}
//�ͷŶ�ά����
void free_Aarray2D(void **arr)
{
	if (arr != NULL)
		free(arr);
}
/*
int main()
{
	printf("  C�����ж�̬�������ά���� malloc free\n");  

	printf("����������(�Կո�ֿ�): ");
	int nRow, nCol;
	scanf("%d %d", &nRow, &nCol);

	//��̬���������Ķ�ά����
	int **p = malloc_Array2D<int>(nRow, nCol);

	//Ϊ��ά���鸳ֵ	
	int i, j;	
	for (i = 0; i < nRow; i++)
		for (j = 0; j < nCol; j++)
			p[i][j] = i + j;

	//�����ά����	
	for (i = 0; i < nRow; i++)
	{
		for (j = 0; j < nCol; j++)
			printf("%4d ", p[i][j]);
		putchar('\n');
	}

	free_Aarray2D((void**)p);
	return 0;
}

*/

/////////////////////////////////////////////////////////////////////////
//���ж�̬��������
static void TestNewArray2(int row,int column)
{
	int i,**p=(int**)malloc(row*sizeof(int));
	p[0]=(int*)malloc(row*column*sizeof(int));
	for(i=1;i<row;i++)
		p[i]=p[0]+i*column;

	//���ö�ά����
	for (int k = 0; k < row; k++)
	{
		for (int j = 0; j < column; j++)
			p[k][j]=j;
	}

	//�����ά����
	for (int k = 0; k < row; k++)
	{
		for (int j = 0; j < column; j++)
			printf("%5d", p[k][j]);
		putchar('\n');
	}

	if (p != NULL)
		free(p);
}

//�д�С�̶��Ķ�ά�����������һά���ݲ���ָ��ǿת�ɶ�ά����
const int MAXCOL = 3;	//��ֵ�̶�
static int TestNewArray()
{
	printf("  �д�С�̶��Ķ�ά�����������һά���ݲ���ָ��ǿת�ɶ�ά����\n");  

	int nRow;
	printf("�������ά���������(��ֵ�̶�Ϊ%d): ", MAXCOL);
	scanf("%d", &nRow);

	//����һά���ݲ�����ת�ɶ�ά����ָ��
	int *pp_arr = new int[nRow * MAXCOL];
	int (*p)[MAXCOL] = (int(*)[MAXCOL])pp_arr;

	//Ϊ��ά���鸳ֵ
	int i, j;
	for (i = 0; i < nRow; i++)
		for (j = 0; j < MAXCOL; j++)
			p[i][j] = i + j;

	//�����ά����
	for (i = 0; i < nRow; i++)
	{
		for (j = 0; j < MAXCOL; j++)
			printf("%5d", p[i][j]);
		putchar('\n');
	}

	//�ͷ���Դ
	delete[] pp_arr;
	return 0;
}
