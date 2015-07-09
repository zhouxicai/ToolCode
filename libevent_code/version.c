// gcc getVersion.c -o getVersion -levent

#include <event.h>
#include <stdio.h>

int main()
{
    const char *version = event_get_version();
    printf("%s\n",version);
    return 0;
}
