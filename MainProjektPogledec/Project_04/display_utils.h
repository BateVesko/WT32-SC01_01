//Project_03
#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <TFT_eSPI.h>
#include "memory_utils.h"

extern TFT_eSPI tft; // Деклариране на външен обект за дисплея

// Глобална променлива за предишната стойност на свободната памет
uint32_t prevFreeHeap = 0;

// Глобални променливи за температурите
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;

// Флаг за показване дали текстът за паметта е вече изписан
bool memoryTextDisplayed = false;

int randomTemperature() {
  return (rand() % 45) - 9; // Генерира случайно число между -9 и 35
}

// Функция за изобразяване на IP адреса
void displayIPAddress() {
  uint16_t colorBackIP = tft.color565(247, 247, 0);
  tft.fillRect(80, 0, 196, 22, colorBackIP);
  tft.setCursor(82, 4);
  tft.setTextColor(TFT_BLUE, colorBackIP);
  tft.setTextSize(2);
  tft.printf("IP %s", WiFi.localIP().toString().c_str());
}

// Функция за изобразяване на информация за паметта и брояча
void displayMemoryInfo(int counter) {
  uint16_t colorBack = tft.color565(0, 247, 247);
  uint32_t freeHeap = ESP.getFreeHeap();
  freeHeap += 0 * counter;

  // Генериране на случайни температури
  temp1 = randomTemperature();
  temp2 = randomTemperature();
  temp3 = randomTemperature();

  // Изобразяване на температурите с кръгчета
  uint16_t circleColor = TFT_BLUE;
  uint16_t borderColor = TFT_RED;
  uint16_t numberColor = tft.color565(255, 255, 0);
  // tft.fillCircle(130, 116, 14, circleColor); // Диаметър 30 пиксела
  // tft.drawCircle(130, 116, 14, borderColor);
  // tft.setCursor(119, 109);
  // tft.setTextColor(numberColor, circleColor);
  // tft.setTextSize(2);
  // tft.printf("%2d", temp1);
  tft.fillRoundRect(100, 95, 60, 25, 5, circleColor); // Запълнен правоъгълник с радиус на закръгляне 10 пиксела
  tft.drawRoundRect(100, 95, 60, 25, 5, borderColor); // Граница на правоъгълник с радиус на закръгляне 10 пиксела
  tft.setCursor(108, 100);
  tft.setTextColor(numberColor, circleColor);
  tft.setTextSize(2);
  tft.printf("%2d", temp1);
  tft.print((char)247); // Unicode за градуса символ (°)
  tft.print("C"); // Добавете 'C' за Целзий


  // tft.fillCircle(376, 77, 14, circleColor);
  // tft.drawCircle(376, 77, 14, borderColor);
  // tft.setCursor(365, 70);
  // tft.setTextColor(numberColor, circleColor);
  // tft.setTextSize(2);
  // tft.printf("%2d", temp2);
  tft.fillRoundRect(336, 65, 60, 25, 5, circleColor); // Запълнен правоъгълник с радиус на закръгляне 10 пиксела
  tft.drawRoundRect(336, 65, 60, 25, 5, borderColor); // Граница на правоъгълник с радиус на закръгляне 10 пиксела
  tft.setCursor(344, 70);
  tft.setTextColor(numberColor, circleColor);
  tft.setTextSize(2);
  tft.printf("%2d", temp2);
  tft.print((char)247); // Unicode за градуса символ (°)
  tft.print("C"); // Добавете 'C' за Целзий

  // tft.fillCircle(354, 194, 14, circleColor);
  // tft.drawCircle(354, 194, 14, borderColor);
  // tft.setCursor(343, 187);
  // tft.setTextColor(numberColor, circleColor);
  // tft.setTextSize(2);
  // tft.printf("%2d", temp3);
  tft.fillRoundRect(324, 193, 60, 25, 5, circleColor); // Запълнен правоъгълник с радиус на закръгляне 10 пиксела
  tft.drawRoundRect(324, 193, 60, 25, 5, borderColor); // Граница на правоъгълник с радиус на закръгляне 10 пиксела
  tft.setCursor(332, 198);
  tft.setTextColor(numberColor, circleColor);
  tft.setTextSize(2);
  tft.printf("%2d", temp3);
  tft.print((char)247); // Unicode за градуса символ (°)
  tft.print("C"); // Добавете 'C' за Целзий

  // Визуализация на паметта и брояча най-долу
  if (!memoryTextDisplayed) {
    tft.fillRect(80, tft.height() - 20, 320, 20, colorBack);
    tft.setCursor(86, tft.height() - 17);
    tft.setTextColor(TFT_RED, colorBack);
    tft.setTextSize(2);
    tft.printf("Free heap:%6u Counter:%1d", freeHeap, counter);
    memoryTextDisplayed = true;
    prevFreeHeap = freeHeap;
  } 
  else 
  {
    if (freeHeap != prevFreeHeap) {
      tft.fillRect(203, tft.height() - 20, 78, 20, TFT_BLUE);
      tft.setCursor(207, tft.height() - 17);
      tft.setTextColor(TFT_YELLOW, TFT_BLUE);
      tft.setTextSize(2);
      tft.printf("%6u", freeHeap);
      prevFreeHeap = freeHeap;
    }

    tft.fillRect(383, tft.height() - 20, 30, 20, TFT_BLUE);
    tft.setCursor(387, tft.height() - 17);
    tft.setTextColor(TFT_YELLOW, TFT_BLUE);
    tft.setTextSize(2);
    tft.printf("%2d", counter);
  }
}

#endif // DISPLAY_UTILS_H
