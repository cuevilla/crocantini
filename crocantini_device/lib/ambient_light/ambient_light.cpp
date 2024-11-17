#include <ambient_light.h>

// local functions
#define AMBIENT_LIGHT_PIN A0

static SharedData_t *shared_data;

void ambient_light_init(SharedData_t *shared) {
    shared_data = shared;
}

void ambient_light_task(void) {
    // connect to A0 Pin (Voltage Range between 0~3.3V for NodeMCU)
    uint16_t adc_read = analogRead(AMBIENT_LIGHT_PIN);
    shared_data->light_intensity = adc_read / 100 + 1;
    Serial.printf("%d\n", adc_read);
}
