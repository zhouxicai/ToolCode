/* main.c */
#include <stdio.h>
#include "CallBack.h"
#include "NewArray.h"
#include "CopyMulitiArray.h"
#include "MySort.h"
#include "FilesCPP.h"
#include "FilesC.h"

void say_hello(void *str)
{
	printf("Hello %s\n", (const char *)str);
}

void count_numbers(void *num)
{
	int i;
	for(i=1; i<=(int)num; i++)
		printf("%d ", i);
	putchar('\n');
}

#if 0
int main(void)
{
	repeat_three_times(say_hello, "Guys");
	repeat_three_times(count_numbers, (void *)4);

	while(1);
	return 0;
}
#endif


int main(void)
{
	//int row,column;
	//printf("请输入二维数组的行数列值");
	//scanf("%d,%d", &row,&column);

	//TestNewArray();
	//TestNewArray2(row,column);
	InitTestDada(16,16,3);
	CopyMulitiArray(5, 4, 0, 0, 6, 8, 16, 16, 3);

	//Bubbing(g_GuideInfo, 10);
	//TestQuickSort();


	while(1);
	return 0;
}