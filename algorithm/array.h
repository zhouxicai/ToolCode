#include"common.h"
// ����N�������ÿո���������Է���N����������
int* find_num(int & num)
{
	const int MAX = 5;
	char str[MAX];
	long sum=0;

	int i=0,top=0;
	fgets(str,MAX,stdin);
	int len = strlen(str);
	printf("size:%d\n",len);

	len = (len+1)*2;//���鳤��
	if (len < sizeof(int))
		len = sizeof(int);
	
	int *ar = (int *)malloc(len);

	while(str[i]!='\0')
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			sum=sum*10+(str[i]-'0');//��������ת��Ϊ��.
		}
		else
		{
			if(sum!=0)//���������
			{
				ar[top++]= sum;
				sum=0;
			}
		}
		i++;
	}
	//�ж����һ���ַ��Ƿ�����
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