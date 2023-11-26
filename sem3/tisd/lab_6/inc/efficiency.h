#ifndef EFFICIENCY_H__
#define EFFICIENCY_H__

#include <stdlib.h>

unsigned long long ms_now(void);

double get_tavg(unsigned long long *t, size_t len_t);

double get_rse(unsigned long long *t, size_t len_t);











#endif

