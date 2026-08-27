#include "LedControl.h"

LedControl::LedControl(int ledPin)
{
    _ledPin = ledPin;
}

void LedControl::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    // On-device test confirmed this board's onboard RGB LED has its
    // red/green argument slots swapped versus neopixelWrite()'s usual
    // (pin, red, green, blue) order - blue is correct as-is.
    neopixelWrite(_ledPin, g, r, b);
}

void LedControl::begin()
{
    // neopixelWrite() drives the addressable RGB LED directly over the RMT
    // peripheral - no ledcAttach()/pinMode() setup needed, just start off.
    off();
}

void LedControl::pwm()
{
    // pulse LED (amber) to show sleep/disabled state
    for (int duty = 0; duty <= 255; duty++)
    {
        setColor(duty, duty / 2, 0); // amber
        delay(7);
    }

    for (int duty = 255; duty >= 0; duty--)
    {
        setColor(duty, duty / 2, 0);
        delay(7);
    }
}

void LedControl::slowBlink()
{
    // Slow blink (blue) to confirm success & restart
    Serial.println("[STATUS] - slow blink");

    for (int cycle = 0; cycle <= 3; cycle++)
    {
        for (int duty = 0; duty <= 255; duty++)
        {
            setColor(0, 0, duty); // blue
            delay(7);
        }

        for (int duty = 255; duty >= 0; duty--)
        {
            setColor(0, 0, duty);
            delay(7);
        }
        delay(150);
    }
}

void LedControl::fastBlink()
{
    // Fast blink (red) to confirm resetting
    Serial.println("[STATUS] - fast blink");
    for (int i = 0; i < 12; i++)
    {

        for (int duty = 0; duty <= 255; duty++)
        {
            setColor(duty, 0, 0); // red
            delay(2);
        }

        for (int duty = 255; duty >= 0; duty--)
        {
            setColor(duty, 0, 0);
            delay(2);
        }

        delay(50);
    }
}

void LedControl::solidOn()
{
    // Solid white while the WiFi setup Access Point is running
    setColor(40, 40, 40);
}

void LedControl::off()
{
    setColor(0, 0, 0);
}

int LedControl::getPin()
{
    return _ledPin;
}
