#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

const int LED_RED_PIN = 7;
const int LED_BLUE_PIN = 8;

void task1(void *parameters) {
  digitalWrite(LED_RED_PIN, HIGH);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  digitalWrite(LED_RED_PIN, LOW);
  vTaskDelay(100 / portTICK_PERIOD_MS);
}

void task2(void *parameters) {
  digitalWrite(LED_BLUE_PIN, HIGH);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  digitalWrite(LED_BLUE_PIN, LOW);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void setup() {
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  xTaskCreate(
    task1, // function name
    "Task 1", // task name
    1000, // stack size
    NULL, // task parameters
    1, // task priority
    NULL // task handle
  );

  // Doen't work for Arduino Uno if try to use both tasks.
  // Works only one of them.

  // xTaskCreate(
  //   task2, // function name
  //   "Task 2", // task name
  //   1000, // stack size
  //   NULL, // task parameters
  //   1, // task priority
  //   NULL // task handle
  // );
}

void loop() {
  
}