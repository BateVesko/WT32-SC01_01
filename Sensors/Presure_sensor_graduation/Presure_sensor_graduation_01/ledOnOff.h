#ifndef LEDONOFF_H
#define LEDONOFF_H

#include <Arduino.h>

void initLED(int pin) {
  pinMode(pin, OUTPUT);
}

void ledOn(int pin) {
  digitalWrite(pin, HIGH);
}

void ledOff(int pin) {
  digitalWrite(pin, LOW);
}

// Разпределение на пиновете:
// 04_+3.3v
// 14_IO12
// 24_IO0 (аналогов вход)
// 34_GND
// 06_GND
// 16_IO13 (светодиод)
// 26_IO5

#endif
