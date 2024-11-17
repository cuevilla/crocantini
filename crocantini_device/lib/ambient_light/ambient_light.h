#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <shared_data.h>

void ambient_light_init(SharedData_t*);
void ambient_light_task(void);

#ifdef __cplusplus
}
#endif

#endif
