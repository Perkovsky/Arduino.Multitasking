#include <Arduino.h>
#include <TaskScheduler.h>

const int LED_RED_PIN = 7;
const int LED_BLUE_PIN = 8;

Scheduler scheduler;

void blinkLedRed() {
  digitalWrite(LED_RED_PIN, !digitalRead(LED_RED_PIN));
}

void blinkLedBlue() {
  digitalWrite(LED_BLUE_PIN, !digitalRead(LED_BLUE_PIN));
}

Task taskBlinkLedRed(100, TASK_FOREVER, &blinkLedRed);
Task taskBlinkLedBlue(1000, TASK_FOREVER, &blinkLedBlue);

void setup() {
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  scheduler.addTask(taskBlinkLedRed);
  scheduler.addTask(taskBlinkLedBlue);
  scheduler.enableAll();
}

void loop() {
  scheduler.execute();
}