///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//   DESCRIPTION: blinking a red LED for 5 seconds and a blue LED for 100 milliseconds   //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>

const int RED_LED_PIN = 4;
const int BLUE_LED_PIN = 5;

void blinkRedLED(void *parameter) {
    while (true) {
        digitalWrite(RED_LED_PIN, HIGH);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        digitalWrite(RED_LED_PIN, LOW);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void blinkBlueLED(void *parameter) {
    while (true) {
        digitalWrite(BLUE_LED_PIN, HIGH);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        digitalWrite(BLUE_LED_PIN, LOW);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    // Note that xTaskCreatePinnedToCore() is used to create the tasks and pin them to a specific core.
    // In this case, the red LED task is pinned to core 0 and the blue LED task is pinned to core 1.
    xTaskCreatePinnedToCore(blinkRedLED, "Blink Red LED", 2048, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(blinkBlueLED, "Blink Blue LED", 2048, NULL, 1, NULL, 1);
}

void loop() {
    // do nothing here
}