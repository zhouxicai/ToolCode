//C++语言中动态的申请二维数组 new delete
#include <new>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;
//动态申请二维数组
template <typename T>
T** new_Array2D(int row, int col)
{
	int size = sizeof(T);
	int point_size = sizeof(T*);
	//先申请内存，其中sizeof(T*) * row表示存放row个行指针
	T **arr = (T **) malloc(point_size * row + size * row * col);
	if (arr != NULL)
	{	
		T *head = (T*)((int)arr + point_size * row);
		for (int i = 0; i < row; ++i)
		{
			arr[i] =  (T*)((int)head + i * col * size);
			for (int j = 0; j < col; ++j)
				new (&arr[i][j]) T;
		}
	}
	return (T**)arr;
}
//释放二维数组
template <typename T>
void delete_Array2D(T **arr, int row, int col)
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			arr[i][j].~T();
	if (arr != NULL)
		free((void**)arr);
}
/*
int main()
{
	printf("  C++语言中动态的申请二维数组 new delete\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

	printf("请输入行列(以空格分开): ");
	int nRow, nCol;
	scanf("%d %d", &nRow, &nCol);

	//动态申请连续的二维数组
	string **p = new_Array2D<string>(nRow, nCol);

	//为二维数组赋值
	int i, j;
	for (i = 0; i < nRow; i++)
		for (j = 0; j < nCol; j++)
		{
			char szTemp[30];
			sprintf(szTemp, "(第%d行,第%d列)", i, j);
			p[i][j] = szTemp;
		}

		//输出二维数组	
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nCol; j++)
				printf("%s ", p[i][j].c_str());
			putchar('\n');
		}

		delete_Array2D<string>(p, nRow, nCol);
		return 0;
}
*/
