#ifndef __COMMON_H__
#define __COMMON_H__
#include <time.h>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)


typedef struct timespec probe_time;

#define probe_get_time(x) clock_gettime(CLOCK_REALTIME,((struct timespec *)x))
#define probe_ns(x) ((((struct timespec *)x)->tv_sec * 1000000000) + ((struct timespec *)x)->tv_nsec)
#define probe_diff(x,y) (probe_ns(y) - probe_ns(x))
#define probe_logdomain(x) [x logDomain]
#define probe_timestamp() ({probe_time ts; probe_get_time(&ts);probe_ns(&ts);})
#define get_ns_diff(x,y)(y - x)


int gcc_bt_create(void **buf, int depth);
int uw_bt_create(void **buf, int depth);
int __get_backtrace_x86_64(void **ip,int size);
long long ts_diff(struct timespec *start, struct timespec *end);

void * rtGetProc(char * name);
#endif
