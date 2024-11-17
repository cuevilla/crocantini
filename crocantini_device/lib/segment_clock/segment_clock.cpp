#include <segment_clock.h>

#include <SPI.h>

//GPIO OUTPUT SETTINGS
#define  DIGIT_1_PIN  D1
#define  SPI_CS_GPIO_PIN  D8

#define LED_LIGHT_MAX_US 40
#define LED_LIGHT_US 1

// local functions
static void intensity_handler(void);
static void soft_pwm_init(void);

// local variables
static uint8_t digits_7_seg[10] = {
    0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100, 0b11011010, 0b11111010, 0b00001110, 0b11111110, 0b11011110
};
static volatile uint8_t* hour[4];
static volatile uint8_t light_intensity;
static volatile SharedData_t *shared_data;

void segment_clock_init(SharedData_t *shared) {
    // shared data
    light_intensity = 1;
    shared_data = shared;
    // clock
    hour[0] = &digits_7_seg[0];
    hour[1] = &digits_7_seg[0];
    hour[2] = &digits_7_seg[0];
    hour[3] = &digits_7_seg[0];
    // configure SPI
    pinMode(SPI_CS_GPIO_PIN, OUTPUT);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);//8 MBits/s
    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    // configure soft pwm
    soft_pwm_init();
}

static void IRAM_ATTR intensity_handler(void) {
    static uint32_t time_elapsed_tmr_ms = 0;
    static uint32_t digit_nr = 0;
    if (time_elapsed_tmr_ms == 0) {
        digitalWrite(SPI_CS_GPIO_PIN, false);
        // SPI1W0 = *hour[digit_nr];
        // SPI.transfer(*hour[digit_nr]);
        SPI1W0 = *hour[0];
        SPI1CMD |= SPIBUSY;
        // SPI.transfer(*hour[0]);
        if (digit_nr == 0) {
            digitalWrite(DIGIT_1_PIN, true);
        }
    } else if (time_elapsed_tmr_ms == light_intensity) {
        digitalWrite(SPI_CS_GPIO_PIN, true);
        if (digit_nr == 0) {
            digitalWrite(DIGIT_1_PIN, false);
        }
        digit_nr = (digit_nr + 1) % 4;
    }
    time_elapsed_tmr_ms++;
    time_elapsed_tmr_ms = time_elapsed_tmr_ms % LED_LIGHT_MAX_US;
}

static void soft_pwm_init(void) {
    // configure gpio
    pinMode(DIGIT_1_PIN, OUTPUT);
    digitalWrite(DIGIT_1_PIN, true);
    // configure timer
    timer1_attachInterrupt(intensity_handler);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
    timer1_write(250);
}

/******************************************************************************
 * FunctionName : clock_task
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void segment_clock_task(void) {
    // increment time
    shared_data->second += 1;
    shared_data->minute += shared_data->second / 60;
    shared_data->hour += shared_data->minute / 60;
    shared_data->second = shared_data->second % 60;
    shared_data->minute = shared_data->minute % 60;
    shared_data->hour = shared_data->hour % 24;
    // update light intensity shadow value
    if (shared_data->light_intensity > LED_LIGHT_MAX_US) {
        light_intensity = LED_LIGHT_MAX_US;
    } else {
        light_intensity = shared_data->light_intensity;
    }
    hour[0] = &digits_7_seg[shared_data->second % 10];
    Serial.printf("%d:%d:%d\n", shared_data->hour, shared_data->minute, shared_data->second);
}
