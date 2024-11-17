#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct {
  uint8_t light_intensity;
} SharedData_t;

#ifdef __cplusplus
}
#endif

#endif