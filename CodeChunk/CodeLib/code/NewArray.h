//C语言中动态的申请二维数组 malloc free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//动态申请二维数组
template <typename T>
T** malloc_Array2D(int row, int col)
{
	int size = sizeof(T);
	int point_size = sizeof(T*);
	//先申请内存，其中point_size * row表示存放row个行指针
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
//释放二维数组
void free_Aarray2D(void **arr)
{
	if (arr != NULL)
		free(arr);
}
/*
int main()
{
	printf("  C语言中动态的申请二维数组 malloc free\n");  

	printf("请输入行列(以空格分开): ");
	int nRow, nCol;
	scanf("%d %d", &nRow, &nCol);

	//动态申请连续的二维数组
	int **p = malloc_Array2D<int>(nRow, nCol);

	//为二维数组赋值	
	int i, j;	
	for (i = 0; i < nRow; i++)
		for (j = 0; j < nCol; j++)
			p[i][j] = i + j;

	//输出二维数组	
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
//行列动态分配数组
static void TestNewArray2(int row,int column)
{
	int i,**p=(int**)malloc(row*sizeof(int));
	p[0]=(int*)malloc(row*column*sizeof(int));
	for(i=1;i<row;i++)
		p[i]=p[0]+i*column;

	//设置二维数组
	for (int k = 0; k < row; k++)
	{
		for (int j = 0; j < column; j++)
			p[k][j]=j;
	}

	//输出二维数组
	for (int k = 0; k < row; k++)
	{
		for (int j = 0; j < column; j++)
			printf("%5d", p[k][j]);
		putchar('\n');
	}

	if (p != NULL)
		free(p);
}

//列大小固定的二维数组可以申请一维数据并将指针强转成二维数组
const int MAXCOL = 3;	//列值固定
static int TestNewArray()
{
	printf("  列大小固定的二维数组可以申请一维数据并将指针强转成二维数组\n");  

	int nRow;
	printf("请输入二维数组的行数(列值固定为%d): ", MAXCOL);
	scanf("%d", &nRow);

	//申请一维数据并将其转成二维数组指针
	int *pp_arr = new int[nRow * MAXCOL];
	int (*p)[MAXCOL] = (int(*)[MAXCOL])pp_arr;

	//为二维数组赋值
	int i, j;
	for (i = 0; i < nRow; i++)
		for (j = 0; j < MAXCOL; j++)
			p[i][j] = i + j;

	//输出二维数组
	for (i = 0; i < nRow; i++)
	{
		for (j = 0; j < MAXCOL; j++)
			printf("%5d", p[i][j]);
		putchar('\n');
	}

	//释放资源
	delete[] pp_arr;
	return 0;
}
