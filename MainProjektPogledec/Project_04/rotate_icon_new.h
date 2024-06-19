//Project_03
#ifndef ROTATE_ICON_NEW_H
#define ROTATE_ICON_NEW_H

//#include <Arduino.h>
//#include <TFT_eSPI.h>
//#include <PNGdec.h>
#include "images/rotate_icons_new/fan_0_new.h"
#include "images/rotate_icons_new/fan_1_new.h"
#include "images/rotate_icons_new/fan_2_new.h"
#include "images/rotate_icons_new/fan_3_new.h"

// Глобални променливи за текущата позиция на иконата
int currentIconXpos_new;
int currentIconYpos_new;

// Функция за изобразяване на икона
void pngDrawNew(PNGDRAW* pDraw) {
  extern TFT_eSPI tft;
  extern PNG png;
  uint16_t lineBuffer[80]; // Размер на буфера за един ред пиксели
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(currentIconXpos_new, currentIconYpos_new + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

// Функция за въртене на иконите
void rotate_icon_new(TFT_eSPI &tft, PNG &png, int Ix, int Iy, int index, char direction) {
  // Масив с иконите
  const unsigned char* icons_new[] = { fan_0_new, fan_1_new, fan_2_new, fan_3_new };
  int num_icons_new = 4;

  // Индекси за въртене
  int indices_new[] = {0, 1, 2, 3};

  // Обърнати индекси за обратно въртене
  if (direction == 'l') {
    indices_new[0] = 3;
    indices_new[1] = 2;
    indices_new[2] = 1;
    indices_new[3] = 0;
  }

  currentIconXpos_new = Ix;
  currentIconYpos_new = Iy;
  int16_t rc = png.openFLASH((uint8_t*)icons_new[indices_new[index]], sizeof(fan_0_new), pngDrawNew);
  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    png.decode(NULL, 0);
    tft.endWrite();
    //Serial.print("Текуща позиция NEW: ");
    //Serial.println(index);
  } else {
    Serial.print("PNG error: ");
    Serial.println(rc);
  }
}

#endif // ROTATE_ICON_NEW_H
