#include <iostream>
using namespace std;


void QuickSort(int arr[], int _left, int _right);
void TestQuickSort()
{
	int aa[50] ={5,23,12,143,80,69,8,12,32,619,
				 15,23,312,413,30,26,8,212,72,119,
				 59,36,122,3,17,86,18,32,62,29,
				 25,29,1,243,40,6,118,52,11,19,
				 35,13,92,432,18,36,84,112,23,39,};
	QuickSort(aa, 0, 49);
	for(int i = 0 ; i<50; i++)
	{
		cout<<aa[i]<<" ";
	}
	while(1);
}

//快速排序
void QuickSort(int arr[], int _left, int _right)
{
    if (_left < _right)
    {
        int left = _left, right = _right, left_value = arr[_left];

        while(left < right)
        {
	 		// 从右向左找第一个小于left_value的数
            while(left < right && arr[right] >= left_value) 
            right--;  

            if(left < right) 
            arr[left++] = arr[right];

	 		// 从左向右找第一个大于等于left_value的数
            while(left < right && arr[left] < left_value) 
            left++;  

            if(left < right) 
            arr[right--] = arr[left];
        }

        arr[left] = left_value;
		// 递归调用 
		QuickSort(arr, _left, left - 1);
		QuickSort(arr, left + 1, _right);
    }

}

////////////////////////////////////////////////////////////////////////
int nMax = 10;
int g_GuideInfo[10] = { 21, 56, 3, 56, 76, 5, 3, 34, 12, 8 };

//冒泡排序
void Bubbing(int arr[],int lengh)
{
	int iTemp = 0;
	for (int i = 1; i<lengh; i++)
	{
		for (int j = lengh - 1; j >= i; j--)
		{
			if (arr[j] > arr[j - 1])
			{
				iTemp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = iTemp;
			}
		}
	}
}
