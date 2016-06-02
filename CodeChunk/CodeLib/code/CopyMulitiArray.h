#include <stdio.h>
#include <vector>

const int MAX_X=16;
const int MAX_Y=16;
int map[MAX_X][MAX_Y];

void InitTestDada()
{
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			map[i][j] = i+j;
}


void CopyMulitiArray(int begin_x,int begin_y,int end_x,int end_y,int target_x,int target_y)
{
	InitTestDada();

#if 1
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
			printf("%3d", map[i][j]);
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

	int target_end_x = target_x + (end_x - begin_x);
	int target_end_y = target_y + (end_y - begin_y);

	//Copy data
	std::vector<int> vecTmp;
	for (int i = begin_x; i < end_x; i++)
		for (int j = begin_y; j < end_y; j++)
			vecTmp.push_back(map[i][j]);

	int k=0;
	for (int i = target_x; i < target_end_x; i++)
	{
		for (int j = target_y; j < target_end_y; j++)
		{
			if (i >= MAX_X)
			{
				k++; continue;
			}
			if (j >= MAX_Y)
			{
				k++; continue;
			}

			map[i][j] = vecTmp[k];

			k++;
		}
	}

#if 1
	putchar('\n');
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
			printf("%3d", map[i][j]);
		putchar('\n');
	}
#endif
}