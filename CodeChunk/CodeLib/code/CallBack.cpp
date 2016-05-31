
/* para_callback.c */
#include "CallBack.h"

void repeat_three_times(callback_t f, void *para)
{
	f(para);
	f(para);
	f(para);
}
