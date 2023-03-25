#include <Arduino.h>
#include <Thread.h>
#include "ThreadController.h"

const int LED_RED_PIN = 7;
const int LED_BLUE_PIN = 8;
const int BUZZER_PIN = 12;

Thread redLedThread = Thread();
Thread blueLedThread = Thread();
Thread buzzerThread = Thread();

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

// Define the BUZZER thread function
void buzzerThreadFunction() {
  // commented code has been transformed to correct (without delay())
  //
  // noTone(BUZZER_PIN);
  // tone(BUZZER_PIN, 440, 200);
  // delay(300);
  //
  // noTone(BUZZER_PIN);
  // tone(BUZZER_PIN, 494, 500);
  // delay(300);

  // 1st solution
  const int notes[] = {440, 300};
  const int noteDurations[] = {200, 300};
  static int noteIndex = 0;
  static unsigned long lastNoteTime = 0;
  unsigned long currentTime = millis();
  
  if (currentTime - lastNoteTime >= noteDurations[noteIndex]) {
    lastNoteTime = currentTime;
    tone(BUZZER_PIN, notes[noteIndex], noteDurations[noteIndex]);
    noteIndex = (noteIndex + 1) % 2;
  }
  // else if (currentTime - lastNoteTime >= 100 - noteDurations[noteIndex]) {
  //   noTone(BUZZER_PIN);
  // }
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
  buzzerThread.onRun(buzzerThreadFunction);
  buzzerThread.setInterval(300);

  // Start the threads
  redLedThread.enabled = true;
  blueLedThread.enabled = true;
  buzzerThread.enabled = true;
}

void loop() {
  if (redLedThread.shouldRun())
		redLedThread.run();

  if (blueLedThread.shouldRun())
		blueLedThread.run();

  if (buzzerThread.shouldRun())
		buzzerThread.run();
}