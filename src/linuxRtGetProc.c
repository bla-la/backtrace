#include <stdio.h>
#define __USE_GNU
#include <dlfcn.h>


void *
rtGetProc(char * name)
{
    return dlsym(RTLD_NEXT,name);
}
