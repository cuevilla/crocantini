#include <Arduino.h>

#include <TaskScheduler.h>
#include <ambient_light.h>

static Scheduler runner;
static Task ambient_light(2000, TASK_FOREVER, ambient_light_task);

static SharedData_t shared_data;

void setup() {
  // initialize the serial console
  Serial.begin(115200);
  // init the ambient light library
  ambient_light_init(&shared_data);
  // add the task to the scheduler
  runner.addTask(ambient_light);
  // enable the task
  ambient_light.enable();
}

void loop() {
  // put your main code here, to run repeatedly:
  runner.execute();
}