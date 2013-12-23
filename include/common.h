#ifndef __COMMON_H__
#define __COMMON_H__



int gcc_bt_create(void **buf, int depth);
int uw_bt_create(void **buf, int depth);
int __get_backtrace_x86_64(void **ip,int size);
long long ts_diff(struct timespec *start, struct timespec *end);

#endif
