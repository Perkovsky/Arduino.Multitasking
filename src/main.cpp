#include <Arduino.h>
#include <Thread.h>
#include "ThreadController.h"

const int LED_RED_PIN = 7;
const int LED_BLUE_PIN = 8;

Thread redLedThread = Thread();
Thread blueLedThread = Thread();

// Define the LED RED thread function
void redLedThreadFunction() {
  static bool redLedState = false;
  redLedState = !redLedState;
  digitalWrite(LED_RED_PIN, redLedState ? HIGH : LOW);
}

// Define the LED BLUE thread function
void blueLedThreadFunction() {
  static bool blueLedState = false;
  blueLedState = !blueLedState;
  digitalWrite(LED_BLUE_PIN, blueLedState ? HIGH : LOW);
}

void setup() {
  // Set the LED pins as outputs
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  // Set up the threads
  redLedThread.onRun(redLedThreadFunction);
  redLedThread.setInterval(100);
  blueLedThread.onRun(blueLedThreadFunction);
  blueLedThread.setInterval(1000);

  // Start the threads
  redLedThread.enabled = true;
  blueLedThread.enabled = true;
}

void loop() {
  if (redLedThread.shouldRun())
		redLedThread.run();

  if (blueLedThread.shouldRun())
		blueLedThread.run();
}