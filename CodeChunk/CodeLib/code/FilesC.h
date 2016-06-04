#include <stdio.h>
#include <stdlib.h>
/*
fopen()�����е�һ����ʽ������ʾ�ļ���, ���԰���·�����ļ��������֡���:
"B:TEST.DAT"
"C://TC//TEST.DAT"
�����·��д��"C:/TC/TEST.DAT"�ǲ���ȷ��, ��һ��Ҫ�ر�ע�⡣
�ڶ�����ʽ������ʾ���ļ������͡������ļ����͵Ĺ涨�μ��±�
��  �ļ���������
��������������������������������������������������������
�ַ�                ����
��������������������������������������������������������
"r"           �������ļ�ֻ��
"w"           ���������ļ�ֻд
"a"           ����, ����ļ��������򴴽�һ��
"r+"          ��һ�������ļ���/д
"w+"          ����һ�������ļ���/д
"a+"          �򿪻򴴽�һ���ļ�����
"b"           �������ļ�(���Ժ�����ÿһ�����)
"t"           �����ļ�(Ĭ����)
��������������������������������������������������������
���Ҫ��һ��CCDOS��Ŀ¼��, �ļ���ΪCLIB�Ķ������ļ�, ��д��:
fopen("c://ccdos//clib", "rb");
*/
void TestRead()
{
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	pFile = fopen("myfile.bin", "rb");
	if (pFile == NULL) { fputs("File error", stderr); exit(1); }

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = (char*)malloc(sizeof(char)*lSize);
	if (buffer == NULL) { fputs("Memory error", stderr); exit(2); }

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize) { fputs("Reading error", stderr); exit(3); }

	/* the whole file is now loaded in the memory buffer. */

	// terminate
	fclose(pFile);
	free(buffer);
}

int TestWrite()
{
	FILE * pFile;
	char buffer[] = { 'x', 'y', 'z' };
	pFile = fopen("myfile.bin", "wb");
	fwrite(buffer, sizeof(char), sizeof(buffer), pFile);
	fclose(pFile);
	return 0;
}