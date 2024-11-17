#include <Arduino.h>

#include <TaskScheduler.h>
#include <ambient_light.h>
#include <segment_clock.h>

static Scheduler runner;
static Task ambient_light(2000, TASK_FOREVER, ambient_light_task);
static Task segment_clock(1000, TASK_FOREVER, segment_clock_task);

static SharedData_t shared_data;

void setup() {
  // initialize the serial console
  Serial.begin(115200);
  // init the ambient light library
  ambient_light_init(&shared_data);
  // init the segment clock library
  segment_clock_init(&shared_data);
  // add the tasks to the scheduler
  runner.addTask(ambient_light);
  runner.addTask(segment_clock);
  // enable the tasks
  ambient_light.enable();
  segment_clock.enable();
}

void loop() {
  // put your main code here, to run repeatedly:
  runner.execute();
}
