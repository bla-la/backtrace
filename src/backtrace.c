#include <stdio.h>
#include <common.h>


#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <libunwind.h>
#include <time.h>


int
uw_bt_create(void **buf, int depth)
{

    unw_cursor_t cursor;
    unw_word_t ip;
    unw_context_t uc;
#ifdef __DEBUG_TIME__
    static int time_count = 0;
    struct timespec stime,etime;
    static unsigned long long timetotal = 0;

    clock_gettime(CLOCK_REALTIME,&stime);
#endif

    unw_getcontext(&uc);
    unw_init_local(&cursor, &uc);
    int i = 0;

    while(unw_step (&cursor) > 0 && i < depth)
    {
        unw_get_reg(&cursor, UNW_REG_IP, &ip);
        buf[i] = (void *)ip;
        i++;
    }
#ifdef __DEBUG_TIME__
    clock_gettime(CLOCK_REALTIME,&etime);
    timetotal += ts_diff(&stime,&etime);
    time_count ++;
    if (!(time_count % 10000)) {
        printf("avg backtrace time %f\n",(timetotal/time_count)/1000000000.0);
        time_count = 0;
        timetotal = 0;
    }
#endif
  return i - 2;
}


int
gcc_bt_create(void **buf, int depth)
{
    size_t size;
#ifdef __DEBUG_TIME__
    static int time_count = 0;
    struct timespec stime,etime;
    static unsigned long long timetotal = 0;

    clock_gettime(CLOCK_REALTIME,&stime);
#endif

    size = __get_backtrace_x86_64(buf,depth);

#ifdef __DEBUG_TIME__
    clock_gettime(CLOCK_REALTIME,&etime);
    timetotal += ts_diff(&stime,&etime);
    time_count ++;
    if (!(time_count % 10000)) {
        printf("avg backtrace time %f\n",(timetotal/time_count)/1000000000.0);
        time_count = 0;
        timetotal = 0;
    }

#endif
    return size;
}


