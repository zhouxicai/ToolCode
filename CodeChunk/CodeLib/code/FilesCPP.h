#ifndef  FILE_CLASS_DEFINE
#define  FILE_CLASS_DEFINE
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "windows.h"
class File
{
public:
	File()
	{
	  this->f=NULL ;
	  this->path="" ;
	  this->modeAttribute="";
	}
	File(char*path,char * mode)
	{
		FILE *p = fopen(path, mode);
		this->path = path;
		this->modeAttribute = mode;
		if (p == NULL)
		{
			printf("�ļ���ʧ��!\n");
			return;
		}
		this->f = p;
	}
	 ~File()
	 {   
	  if (!this->f==NULL)
	  {
	   fclose(this->f) ;
	  }
  
	 }
	 bool WriteTextToFile(char nChar[],int length)
	 {   
	  if(this->f==NULL)
	  {
	   printf("���ȴ��ļ�!\n")  ;
	  }
	  int item= fwrite(nChar,1,length,this->f) ;
	  if (item<length)
	  {
	   return false ;
	  }
	  return true ;
	 }
	 FILE * GetFilePointer()
	 {
	  return this->f;
	 }
	 int  ReadAllText(char buf[])
	 {     
	  char tem[11] ="";
	  while (!feof(f))
	  {   
	   memset(tem,0,11) ;
	   int len=fread(tem,1,10,this->f);
	   strcat(buf,tem);
	  }
  
	  return 1;
	 }
	 void CloseFile()
	 {
	  fclose(this->f) ;
	 }
	 void ClearFile() 
	 {   
	  this->CloseFile() ;//�ر��ļ�
	  //DeleteFile(this->path) ; zhouxicai ע��
	  this->f=fopen(this->path,this->modeAttribute) ;
	 }
	private:
	 FILE * f ;  //����ʵ��ϸ��
	 char * path ;
	 char * modeAttribute  ;
 
};
#endif


#if 0
void main()
{
 File  f("d:\\1.txt","a") ;
 char buf[100]="this is a test!" ;
 f.WriteTextToFile(buf,strlen(buf)) ;
 f.CloseFile() ;
 File f2("d:\\1.txt","a+");
 f2.ReadAllText(buf) ;
 printf(buf) ;
 f2.ClearFile() ;
}
#endif