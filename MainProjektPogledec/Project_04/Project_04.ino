//Project_03
#include <WiFi.h>
#include <WebServer.h>
#include <TFT_eSPI.h>
#include <PNGdec.h>
#include "images.h"
#include "display_utils.h"
#include "rotate_icon_new.h"
#include "HTTPServer.h"

const char *ssid = "TP-Link_1AEA";
const char *password = "83590566";

// Създаване на инстанция на библиотеката TFT_eSPI
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

// Създаване на инстанция на PNG декодера
PNG png; // PNG decoder instance

#define MAX_IMAGE_WIDTH 320 // Adjust for your images

// Структура за съхранение на информация за иконките
struct Icon {
  const uint8_t* data;
  uint32_t size;
  int16_t width;
  int16_t height;
  int16_t xpos;
  int16_t ypos;
};

// Масив от иконки
Icon icons[] = {
  { earth, sizeof(earth), 80, 80, 0, 0 },
  { heater, sizeof(heater), 80, 80, 0, 162 },
  { lamp, sizeof(lamp), 80, 72, 0, 243 },
  { http, sizeof(http), 80, 80, 400, 0 },
  { dust, sizeof(dust), 80, 80, 400, 81 },
  { bell, sizeof(bell), 80, 74, 400, 162 },
  { lock, sizeof(lock), 80, 78, 400, 237 },
  { redutaSmal04, sizeof(redutaSmal04), 320, 243, 80, 30 },
  { color_palette80, sizeof(color_palette80), 5, 100, 400, 315 },
  { color_palette80, sizeof(color_palette80), 5, 100, 0, 315 },
  // Добавете още иконки тук
};

int16_t currentIconXpos;
int16_t currentIconYpos;

unsigned long lastUpdateTime_Count = 0;
unsigned long lastUpdateTime_RotIcon_fan = 0;
int currentIconIndex_fan = 0;
int Ix_fan = 0;
int Iy_fan = 81;
char direction_fan = 'r';
int count_time = 2000;

int counter = 0; // Брояч

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(0xf7be);

  for (int i = 0; i < sizeof(icons) / sizeof(icons[0]); i++) {
    currentIconXpos = icons[i].xpos;
    currentIconYpos = icons[i].ypos;
    displayIcon(icons[i]);
  }

  initWiFiAndServer();

  displayIPAddress();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime_Count >= count_time) {
    lastUpdateTime_Count = currentTime;
    displayMemoryInfo(counter); // Показва брояча
    counter = (counter + 1) % 99; // Увеличаване на брояча ************
  }

  if (currentTime - lastUpdateTime_RotIcon_fan >= 250) {
    lastUpdateTime_RotIcon_fan = currentTime;
    rotate_icon_new(tft, png, Ix_fan, Iy_fan, currentIconIndex_fan, direction_fan);
    currentIconIndex_fan = (currentIconIndex_fan + 1) % 4;
  }

  httpServer.handleClient();
}

void displayIcon(const Icon& icon) {
  int16_t rc = png.openFLASH((uint8_t*)icon.data, icon.size, pngDraw);
  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    uint32_t dt = millis();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

void pngDraw(PNGDRAW* pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(currentIconXpos, currentIconYpos + pDraw->y, pDraw->iWidth, 1, lineBuffer); // Използвайте текущите позиции и pDraw->y
}
