#include <iostream>
#include <assert.h>

//dest比src低，则可以从s头开始拷贝； dest比src高，则为了保证s的数据不会被覆盖，所以要从s的末尾开始拷贝。
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
* 说明：字符串拷贝
* 参数：dest目标地址，src源地址
* 返回：返回拷贝好的地址；如果出错或者有重叠，无定义
* 异常：可能出现字符串溢出，及dest所占空间不如src所占空间大。
*/
char * StrCopy(char * dest, char* src)
{
	assert((dest != NULL) && (src != NULL));

	char * a = dest;

	while((*dest++ = *src++) != '\0');

	return a;
}