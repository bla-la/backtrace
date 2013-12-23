#include <stdio.h>
#include <bits/libc-lock.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unwind.h>


typedef unsigned _Unwind_Word __attribute__((__mode__(__word__)));
typedef unsigned _Unwind_Ptr __attribute__((__mode__(__pointer__)));

struct trace_arg
{
    void **array;
    _Unwind_Word cfa;
    int cnt;
    int size;
};


//static _Unwind_Reason_Code (*unwind_backtrace) (_Unwind_Trace_Fn, void *);
//static _Unwind_Ptr (*unwind_getip) (struct _Unwind_Context *);
//static _Unwind_Word (*unwind_getcfa) (struct _Unwind_Context *);

//_Unwind_Reason_Code _Unwind_Backtrace(_Unwind_Trace_Fn, void *);
//_Unwind_Word _Unwind_GetCFA(struct _Unwind_Context *);
//_Unwind_Ptr _Unwind_GetIP(struct _Unwind_Context *);


static _Unwind_Reason_Code
backtrace_helper (struct _Unwind_Context *ctx, void *a)
{
    struct trace_arg *arg = a;
    if (arg->cnt != -1)
    {
        arg->array[arg->cnt] = (void *) _Unwind_GetIP(ctx);
#ifdef __TEST_ONLY__
        printf("Yahoo ip is 0x%llx\n",arg->array[arg->cnt]);
#endif
        _Unwind_Word cfa  = _Unwind_GetCFA(ctx);

        if (arg->cnt > 0
                && arg->array[arg->cnt - 1] == arg->array[arg->cnt]
                    && cfa == arg->cfa)
            return _URC_END_OF_STACK;
        arg->cfa = cfa;
    }
    if (++arg->cnt == arg->size)
        return _URC_END_OF_STACK;
    return _URC_NO_REASON;
}

int __get_backtrace_x86_64(void **ip,int size)
{
    struct trace_arg arg = { .array = ip, .cfa = 0, .size = size, .cnt = -1 };
    _Unwind_Backtrace(backtrace_helper,&arg);
    return arg.cnt;
}





#ifdef __TEST_ONLY__

int n;
void **arr;
size_t arsz;

f10(){n =  __get_backtrace_x86_64(arr,arsz); printf("bt count %d\n",n);};
f9(){f10();};
f8(){f9();};
f7(){f8();};
f6(){f7();};
f5(){f6();};
f4(){f5();};
f3(){f4();};
f2(){f3();};
f1(){f2();};
f0(){f1();};

int main()
{

    arr = malloc(sizeof(void *) * 128);
    arsz = 128;
    f0();
}
#endif
