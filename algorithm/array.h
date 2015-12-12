#include"common.h"
// 输入N个数，用空格隔开，可以返回N个数的数组
int* find_num(int & num)
{
	const int MAX = 5;
	char str[MAX];
	long sum=0;

	int i=0,top=0;
	fgets(str,MAX,stdin);
	int len = strlen(str);
	printf("size:%d\n",len);

	len = (len+1)*2;//数组长度
	if (len < sizeof(int))
		len = sizeof(int);
	
	int *ar = (int *)malloc(len);

	while(str[i]!='\0')
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			sum=sum*10+(str[i]-'0');//连续数字转换为数.
		}
		else
		{
			if(sum!=0)//保存这个数
			{
				ar[top++]= sum;
				sum=0;
			}
		}
		i++;
	}
	//判断最后一个字符是否是数
	if(sum!=0)
	{
		ar[top++]= sum;
	}
	//print test 
	//i=0;
	//while(i<top)
	//{
	//	printf("a:%ld\n",ar[i]);
	//	i++;
	//}
	num = top;
	return ar;
}