#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct {
  uint8_t light_intensity;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} SharedData_t;

#ifdef __cplusplus
}
#endif

#endif
