//C++�����ж�̬�������ά���� new delete
#include <new>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;
//��̬�����ά����
template <typename T>
T** new_Array2D(int row, int col)
{
	int size = sizeof(T);
	int point_size = sizeof(T*);
	//�������ڴ棬����sizeof(T*) * row��ʾ���row����ָ��
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
//�ͷŶ�ά����
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
	printf("  C++�����ж�̬�������ά���� new delete\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

	printf("����������(�Կո�ֿ�): ");
	int nRow, nCol;
	scanf("%d %d", &nRow, &nCol);

	//��̬���������Ķ�ά����
	string **p = new_Array2D<string>(nRow, nCol);

	//Ϊ��ά���鸳ֵ
	int i, j;
	for (i = 0; i < nRow; i++)
		for (j = 0; j < nCol; j++)
		{
			char szTemp[30];
			sprintf(szTemp, "(��%d��,��%d��)", i, j);
			p[i][j] = szTemp;
		}

		//�����ά����	
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
