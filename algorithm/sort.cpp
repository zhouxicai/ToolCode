#include<iostream>
using namespace std;


//ֱ��˳������
void InsertSort(int r[], int n)
{	
    for (int i=2; i<n; i++)
	{ 
      r[0]=r[i];                        //�����ڱ�
	  for (int j=i-1; r[0]<r[j]; j--)   //Ѱ�Ҳ���λ��
	        r[j+1]=r[j];                //��¼����
	  r[j+1]=r[0];                 
	}
	for(int k=1;k<n;k++)
       cout<<r[k]<<" ";	  
	cout<<"\n";
}




//ϣ������
void ShellSort(int r[], int n)
{	
	int i;
	int d;
	int j;
    for (d=n/2; d>=1; d=d/2)            //������Ϊd����ֱ�Ӳ�������
	{
	     for (i=d+1; i<n; i++)   
		 {   
             r[0]=r[i];                 //�ݴ汻�����¼
               for (j=i-d; j>0 && r[0]<r[j]; j=j-d)
                     r[j+d]=r[j];       //��¼����d��λ��
                          r[j+d]=r[0];
		 }
	}
   for(i=1;i<n;i++)
       cout<<r[i]<<" ";
   cout<<"\n";
}

//��������
void BubbleSort(int r[], int n)
{
	int temp;
	int exchange;
	int bound;
    exchange=n-1;                       //��һ����������ķ�Χ��r[0]��r[n-1]	
	while (exchange)                    //������һ�������м�¼�����Ž��б�������
	{
		bound=exchange; 
		exchange=0;  
	    for (int j=0; j<bound; j++)     //һ����������
	    if (r[j]>r[j+1]) 
		{
		  temp=r[j];
		  r[j]=r[j+1];
		  r[j+1]=temp;
		  exchange=j;                   //��¼ÿһ�η�����¼������λ��
	   }
	}
	for(int i=0;i<n;i++)
       cout<<r[i]<<" ";
	cout<<"\n";
}


//��������һ�λ���
int Partition(int r[], int first, int end)
{	
	int i=first;                        //��ʼ��
	int j=end;
	int temp;        

    while (i<j)	
	{  
       while (i<j && r[i]<= r[j])
			j--;                        //�Ҳ�ɨ��
       if (i<j)
	   { 
			 temp=r[i];                 //����С��¼������ǰ��
	         r[i]=r[j];
	         r[j]=temp;
              i++; 
	   }
       while (i<j && r[i]<= r[j]) 
		   i++;                         //���ɨ��
           if (i<j)
		   {
              temp=r[j];
	          r[j]=r[i];
	          r[i]=temp;                //���ϴ��¼����������
               j--; 
		   }
	}
    return i;                           //iΪ��ֵ��¼������λ��
}

//��������
void QuickSort(int r[], int first, int end)
{
    if (first<end) 
	{                                   //�ݹ����
           int pivot=Partition(r, first, end);  //һ�λ���
           QuickSort(r, first, pivot-1);//�ݹ�ض���������н��п�������
           QuickSort(r, pivot+1, end);  //�ݹ�ض��Ҳ������н��п�������
	}

}

//��ѡ������
void SelectSort(int r[ ], int n)
{ 
	int i;
	int j;
	int index;
	int temp;
    for (i=0; i<n-1; i++)  	            //��n����¼����n-1�˼�ѡ������
	{  
       index=i; 		
       for (j=i+1; j<n; j++)            //����������ѡȡ��С��¼
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


//ɸѡ��������
void Sift(int r[], int k, int m)
{
  
	int i;
	int j;
	int temp;
	i=k; 
	j=2*i+1;                            //��iΪҪɸ�Ľ�㣬jΪi������
  while (j<=m)                          //ɸѡ��û�н��е�Ҷ��
  {
      if (j<m && r[j]<r[j+1]) 
		  j++;                          //�Ƚ�i�����Һ��ӣ�jΪ�ϴ���
      if (r[i]>r[j]) break;             //������Ѿ��������Һ����еĽϴ���
      else 
	  {
           temp=r[i];
	       r[i]=r[j];
		   r[j]=temp;                   //�����������j����
           i=j;
		   j=2*i+1;                     //��ɸ���λ��ԭ�����j��λ��
	 }
  }
}
//������
void HeapSort(int r[ ], int n)
{
   
  int i;
  int temp;
  for (i=n/2; i>=0; i--)                //��ʼ���ѣ������һ�����ն˽���������
     Sift(r, i, n) ;     
   for (i=n-1; i>0; i--)                //�ظ�ִ�����߶Ѷ����ؽ��ѵĲ���
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


//һ�ι鲢
void Merge(int r[], int r1[], int s, int m, int t)
{

	int i=s;
	int j=m+1;
	int k=s;
      
     while (i<=m && j<=t)
	 {   
         if (r[i]<=r[j]) 
			 r1[k++]=r[i++];            //ȡr[i]��r[j]�н�С�߷���r1[k]
         else 
			 r1[k++]=r[j++]; 
	 }
      if (i<=m) 
		  while (i<=m)                  //����һ��������û�����꣬�������β����         
			  r1[k++]=r[i++]; 
      else  
		  while (j<=t)                  //���ڶ���������û�����꣬�������β����        
			r1[k++]=r[j++]; 
}


//һ�˹鲢
void MergePass(int r[ ], int r1[ ], int n, int h)
{
	int i=0;
	int k;

   while (i<=n-2*h)                     //���鲢��¼��������������Ϊh��������
   {
     Merge(r, r1, i, i+h-1, i+2*h-1);
        i+=2*h;
   }
   if (i<n-h) 
	   Merge(r, r1, i, i+h-1, n);       //���鲢��������һ������С��h
   else for (k=i; k<=n; k++)            //���鲢������ֻʣһ��������
        r1[k]=r[k];
}

//�鲢����ķǵݹ��㷨
void MergeSort1(int r[ ], int r1[ ], int n )
{ 
  int h=1;
  int i;

  while (h<n)
  {
    MergePass(r, r1, n-1, h);           //�鲢
    h=2*h;
    MergePass(r1, r, n-1, h);
    h=2*h;
  }
  for(i=0;i<n;i++)
      cout<<r[i]<<" ";
  cout<<"\n";
}

//�鲢����ĵݹ��㷨
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
            MergeSort2(r, r2, r1, s, m);        //�鲢����ǰ���������		
            MergeSort2(r, r2, r1, m+1, t);      //�鲢�������������
            Merge(r2, r1, s, m, t);             //������������������й鲢 		
	}	 
}
