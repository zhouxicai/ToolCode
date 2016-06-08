#include <iostream>
#include <assert.h>

//dest��src�ͣ�����Դ�sͷ��ʼ������ dest��src�ߣ���Ϊ�˱�֤s�����ݲ��ᱻ���ǣ�����Ҫ��s��ĩβ��ʼ������
void  *memmove(void *dest, const void *src, size_t count)
{
	assert((src != NULL) && (dest != NULL));
	char *tmp, *s;

	if (dest <= src)
	{
		tmp = (char *)dest;
		s = (char *)src;
		while (count--)
			*tmp++ = *s++;
	}
	else {
		tmp = (char *)dest + count;
		s = (char *)src + count;
		while (count--)
			*--tmp = *--s;
	}
	return dest;
}

/*
* ˵�����ַ�������
* ������destĿ���ַ��srcԴ��ַ
* ���أ����ؿ����õĵ�ַ���������������ص����޶���
* �쳣�����ܳ����ַ����������dest��ռ�ռ䲻��src��ռ�ռ��
*/
char * StrCopy(char * dest, char* src)
{
	assert((dest != NULL) && (src != NULL));

	char * a = dest;

	while((*dest++ = *src++) != '\0');

	return a;
}