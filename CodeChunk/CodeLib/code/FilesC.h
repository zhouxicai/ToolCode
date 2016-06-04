#include <stdio.h>
#include <stdlib.h>
/*
fopen()函数中第一个形式参数表示文件名, 可以包含路径和文件名两部分。如:
"B:TEST.DAT"
"C://TC//TEST.DAT"
如果将路径写成"C:/TC/TEST.DAT"是不正确的, 这一点要特别注意。
第二个形式参数表示打开文件的类型。关于文件类型的规定参见下表。
表  文件操作类型
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
字符                含义
────────────────────────────
"r"           打开文字文件只读
"w"           创建文字文件只写
"a"           增补, 如果文件不存在则创建一个
"r+"          打开一个文字文件读/写
"w+"          创建一个文字文件读/写
"a+"          打开或创建一个文件增补
"b"           二进制文件(可以和上面每一项合用)
"t"           文这文件(默认项)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
如果要打开一个CCDOS子目录中, 文件名为CLIB的二进制文件, 可写成:
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