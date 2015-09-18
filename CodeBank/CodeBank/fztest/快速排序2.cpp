#include <iostream>  
using namespace std;  


void quick_sort(int arr[], int _left, int _right);

//快速排序;
void quick_sort(int arr[], int _left, int _right)
{

	if (_left < _right)
	{
		int left = _left, right = _right, x = arr[_left];

		while(left < right)
		{
			// 从右向左找第一个小于x的数;
			while(left < right && arr[right] >= x) 
				right--;  

			if(left < right) 
				arr[left++] = arr[right];

			// 从左向右找第一个大于等于x的数;
			while(left < right && arr[left] < x) 
				left++;  

			if(left < right) 
				arr[right--] = arr[left];
		}
		arr[left] = x;
		// 递归调用 ;
		quick_sort(arr, _left, left - 1); 
		quick_sort(arr, left + 1, _right);
	}

}
void test_quick_sort(void)
{
	int aa[50] ={5,23,12,143,80,69,8,12,32,619,
		15,23,312,413,30,26,8,212,72,119,
		59,36,122,3,17,86,18,32,62,29,
		25,29,1,243,40,6,118,52,11,19,
		35,13,92,432,18,36,84,112,23,39,};
	quick_sort(aa,0,49);
	for(int i = 0 ; i<50; i++)
	{
		cout<<aa[i]<<endl;
	}
}

#if 0
void main ()
{
	test_quick_sort();
	while(1);
}
#endif