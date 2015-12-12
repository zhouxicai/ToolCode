#include<iostream>
using namespace std;


//直接顺序排序
void InsertSort(int r[], int n)
{	
    for (int i=2; i<n; i++)
	{ 
      r[0]=r[i];                        //设置哨兵
	  for (int j=i-1; r[0]<r[j]; j--)   //寻找插入位置
	        r[j+1]=r[j];                //记录后移
	  r[j+1]=r[0];                 
	}
	for(int k=1;k<n;k++)
       cout<<r[k]<<" ";	  
	cout<<"\n";
}




//希尔排序
void ShellSort(int r[], int n)
{	
	int i;
	int d;
	int j;
    for (d=n/2; d>=1; d=d/2)            //以增量为d进行直接插入排序
	{
	     for (i=d+1; i<n; i++)   
		 {   
             r[0]=r[i];                 //暂存被插入记录
               for (j=i-d; j>0 && r[0]<r[j]; j=j-d)
                     r[j+d]=r[j];       //记录后移d个位置
                          r[j+d]=r[0];
		 }
	}
   for(i=1;i<n;i++)
       cout<<r[i]<<" ";
   cout<<"\n";
}

//起泡排序
void BubbleSort(int r[], int n)
{
	int temp;
	int exchange;
	int bound;
    exchange=n-1;                       //第一趟起泡排序的范围是r[0]到r[n-1]	
	while (exchange)                    //仅当上一趟排序有记录交换才进行本趟排序
	{
		bound=exchange; 
		exchange=0;  
	    for (int j=0; j<bound; j++)     //一趟起泡排序
	    if (r[j]>r[j+1]) 
		{
		  temp=r[j];
		  r[j]=r[j+1];
		  r[j+1]=temp;
		  exchange=j;                   //记录每一次发生记录交换的位置
	   }
	}
	for(int i=0;i<n;i++)
       cout<<r[i]<<" ";
	cout<<"\n";
}


//快速排序一次划分
int Partition(int r[], int first, int end)
{	
	int i=first;                        //初始化
	int j=end;
	int temp;        

    while (i<j)	
	{  
       while (i<j && r[i]<= r[j])
			j--;                        //右侧扫描
       if (i<j)
	   { 
			 temp=r[i];                 //将较小记录交换到前面
	         r[i]=r[j];
	         r[j]=temp;
              i++; 
	   }
       while (i<j && r[i]<= r[j]) 
		   i++;                         //左侧扫描
           if (i<j)
		   {
              temp=r[j];
	          r[j]=r[i];
	          r[i]=temp;                //将较大记录交换到后面
               j--; 
		   }
	}
    return i;                           //i为轴值记录的最终位置
}

//快速排序
void QuickSort(int r[], int first, int end)
{
    if (first<end) 
	{                                   //递归结束
           int pivot=Partition(r, first, end);  //一次划分
           QuickSort(r, first, pivot-1);//递归地对左侧子序列进行快速排序
           QuickSort(r, pivot+1, end);  //递归地对右侧子序列进行快速排序
	}

}

//简单选择排序
void SelectSort(int r[ ], int n)
{ 
	int i;
	int j;
	int index;
	int temp;
    for (i=0; i<n-1; i++)  	            //对n个记录进行n-1趟简单选择排序
	{  
       index=i; 		
       for (j=i+1; j<n; j++)            //在无序区中选取最小记录
   	     if (r[j]<r[index])
			 index=j;
       if (index!=i) 
	   {
		  temp=r[i];
		  r[i]=r[index];
		  r[index]=temp;
	   }
	}
    for(i=0;i<n;i++)
        cout<<r[i]<<" ";
    cout<<"\n";
}


//筛选法调整堆
void Sift(int r[], int k, int m)
{
  
	int i;
	int j;
	int temp;
	i=k; 
	j=2*i+1;                            //置i为要筛的结点，j为i的左孩子
  while (j<=m)                          //筛选还没有进行到叶子
  {
      if (j<m && r[j]<r[j+1]) 
		  j++;                          //比较i的左右孩子，j为较大者
      if (r[i]>r[j]) break;             //根结点已经大于左右孩子中的较大者
      else 
	  {
           temp=r[i];
	       r[i]=r[j];
		   r[j]=temp;                   //将根结点与结点j交换
           i=j;
		   j=2*i+1;                     //被筛结点位于原来结点j的位置
	 }
  }
}
//堆排序
void HeapSort(int r[ ], int n)
{
   
  int i;
  int temp;
  for (i=n/2; i>=0; i--)                //初始建堆，从最后一个非终端结点至根结点
     Sift(r, i, n) ;     
   for (i=n-1; i>0; i--)                //重复执行移走堆顶及重建堆的操作
   {
	   temp=r[i];
	   r[i]=r[0];
	   r[0]=temp;
      Sift(r, 0, i-1);
   }
   for(i=0;i<n;i++)
      cout<<r[i]<<" ";
   cout<<"\n";
}


//一次归并
void Merge(int r[], int r1[], int s, int m, int t)
{

	int i=s;
	int j=m+1;
	int k=s;
      
     while (i<=m && j<=t)
	 {   
         if (r[i]<=r[j]) 
			 r1[k++]=r[i++];            //取r[i]和r[j]中较小者放入r1[k]
         else 
			 r1[k++]=r[j++]; 
	 }
      if (i<=m) 
		  while (i<=m)                  //若第一个子序列没处理完，则进行收尾处理         
			  r1[k++]=r[i++]; 
      else  
		  while (j<=t)                  //若第二个子序列没处理完，则进行收尾处理        
			r1[k++]=r[j++]; 
}


//一趟归并
void MergePass(int r[ ], int r1[ ], int n, int h)
{
	int i=0;
	int k;

   while (i<=n-2*h)                     //待归并记录至少有两个长度为h的子序列
   {
     Merge(r, r1, i, i+h-1, i+2*h-1);
        i+=2*h;
   }
   if (i<n-h) 
	   Merge(r, r1, i, i+h-1, n);       //待归并序列中有一个长度小于h
   else for (k=i; k<=n; k++)            //待归并序列中只剩一个子序列
        r1[k]=r[k];
}

//归并排序的非递归算法
void MergeSort1(int r[ ], int r1[ ], int n )
{ 
  int h=1;
  int i;

  while (h<n)
  {
    MergePass(r, r1, n-1, h);           //归并
    h=2*h;
    MergePass(r1, r, n-1, h);
    h=2*h;
  }
  for(i=0;i<n;i++)
      cout<<r[i]<<" ";
  cout<<"\n";
}

//归并排序的递归算法
void MergeSort2(int r[], int r1[], int r2[],int s, int t)
{ 
 
	int m;
	if (s==t) 
	{
		r1[s]=r[s];

	}
    else 
	{ 
            m=(s+t)/2;
            MergeSort2(r, r2, r1, s, m);        //归并排序前半个子序列		
            MergeSort2(r, r2, r1, m+1, t);      //归并排序后半个子序列
            Merge(r2, r1, s, m, t);             //将两个已排序的子序列归并 		
	}	 
}
