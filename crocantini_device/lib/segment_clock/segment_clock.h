#ifndef SEGMENT_CLOCK_H
#define SEGMENT_CLOCK_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <shared_data.h>

void segment_clock_init(SharedData_t*);
void segment_clock_task(void);

#ifdef __cplusplus
}
#endif

#endif
