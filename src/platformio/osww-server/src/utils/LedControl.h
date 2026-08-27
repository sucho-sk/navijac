#include <Arduino.h>

#ifndef LedControl_H
#define LedControl_H

// Drives a single addressable RGB LED (WS2812 / NeoPixel), such as the
// onboard status LED on the ESP32-C6-DevKitC-1 (and pin-compatible boards).
// Uses the arduino-esp32 core's built-in neopixelWrite() helper, so no
// external NeoPixel library is required.
class LedControl
{
private:
    int _ledPin;

    // This board's onboard LED has its red/green argument slots swapped
    // (confirmed by an on-device test) - this wraps neopixelWrite() so the
    // rest of the class can just pass normal, intended R/G/B values.
    void setColor(uint8_t r, uint8_t g, uint8_t b);

public:
    LedControl(int ledPin);

    void begin();

    void pwm();

    void slowBlink();

    void fastBlink();

    void solidOn();

    void off();

    int getPin();
};

#endif
