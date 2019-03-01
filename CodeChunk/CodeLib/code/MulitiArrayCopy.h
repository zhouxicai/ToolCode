#include <stdio.h>
#include <vector>

int map[3][16][16];
#define DISABLE_PRINT	1

void InitTestDada(int max_x, int max_y, int max_layer)
{
	for (int l = 0; l < max_layer; l++)
		for (int i = 0; i < max_x; i++)
			for (int j = 0; j < max_y; j++)
				map[l][i][j] = l + i + j;
}


void CopyMulitiArray(int begin_x, int begin_y, int end_x, int end_y, int target_x, int target_y, int max_layer, int max_x, int max_y)
{
#if DISABLE_PRINT
	for (int l = 0; l < max_layer; l++)
	{
		for (int i = 0; i < max_x; i++)
		{
			for (int j = 0; j < max_y; j++)
				printf("%3d", map[l][i][j]);
			putchar('\n');
		}
		putchar('\n');
	}
#endif

	if (begin_x > end_x)
	{
		int tmpx = begin_x;
		begin_x = end_x;
		end_x = tmpx;
	}

	if (begin_y > end_y)
	{
		int tmpy = begin_y;
		begin_y = end_y;
		end_y = tmpy;
	} 
	
	int x_count = end_x - begin_x;
	int y_count = end_y - begin_y;
	int target_end_x = target_x + x_count;
	int target_end_y = target_y + y_count;

	int total = x_count * y_count * max_layer;
	int *tmp_arry = new int[total];
	int arry_index = 0;

	//Copy data
	for (int l = 0; l < max_layer;l++){
		for (int i = begin_x; i < end_x; i++){
			for (int j = begin_y; j < end_y; j++) {
				tmp_arry[arry_index++] = map[l][i][j];
			}
		}
	}
				
	int k = 0;
	for (int l = 0; l < max_layer; l++)
	{
		for (int i = target_x; i < target_end_x; i++)
		{
			for (int j = target_y; j < target_end_y; j++)
			{
				if (i >= max_x)
				{
					k++; continue;
				}
				if (j >= max_y)
				{
					k++; continue;
				}

				map[l][i][j] = tmp_arry[k];

				k++;
			}
		}
	}
	delete[] tmp_arry;
#if DISABLE_PRINT
	printf("=========================================");
	putchar('\n');
	putchar('\n');
	for (int l = 0; l < max_layer; l++)
	{
		for (int i = 0; i < max_x; i++)
		{
			for (int j = 0; j < max_y; j++)
				printf("%3d", map[l][i][j]);
			putchar('\n');
		}
		putchar('\n');
	}
#endif
}