#include <Arduino.h>

#define ANALOG_PIN 2  // Използваме GPIO2 за аналогов вход

const int numMeasurements = 10;  // Брой измервания за осредняване
const int numAverages = 10;  // Брой усреднени стойности за допълнително осредняване

int adcReadings[numMeasurements];  // Масив за съхранение на измерванията
int adcAverages[numAverages];  // Масив за съхранение на усреднените стойности

int adcIndex = 0;  // Индекс за текущото измерване
int avgIndex = 0;  // Индекс за текущата усреднена стойност

unsigned long lastMeasurementTime = 0;
unsigned long lastPrintTime = 0;

void setup() {
  Serial.begin(9600);  // Започваме сериен монитор на 9600 бауда
  analogSetAttenuation(ADC_11db); // Настройка на затихването за обхват 0-3.3V

  Serial.println("Инициализация...");
  delay(5000);  // Пауза за уравновесяване на нивото на стенда

  // Инициализация на масивите с нули
  for (int i = 0; i < numMeasurements; i++) {
    adcReadings[i] = 0;
  }
  for (int i = 0; i < numAverages; i++) {
    adcAverages[i] = 0;
  }

  Serial.println("Инициализация завършена");
}

void loop() {
  unsigned long currentTime = millis();

  // Осредняване на 10 измервания през 0,1 секунда
  if (currentTime - lastMeasurementTime >= 100) {
    lastMeasurementTime = currentTime;

    adcReadings[adcIndex] = analogRead(ANALOG_PIN);
    adcIndex = (adcIndex + 1) % numMeasurements;

    if (adcIndex == 0) {
      // Изчисляване на средната стойност на 10 измервания
      int total = 0;
      for (int i = 0; i < numMeasurements; i++) {
        total += adcReadings[i];
      }
      int average = total / numMeasurements;

      // Съхраняване на усреднената стойност в масива с усреднени стойности
      adcAverages[avgIndex] = average;
      avgIndex = (avgIndex + 1) % numAverages;
    }
  }

  // Принтиране на осредненото измерване на всеки 2 секунди
  if (currentTime - lastPrintTime >= 2000) {
    lastPrintTime = currentTime;

    // Осредняване на последните 10 усреднени стойности
    int avgTotal = 0;
    for (int i = 0; i < numAverages; i++) {
      avgTotal += adcAverages[i];
    }
    int finalAverage = avgTotal / numAverages;

    // Принтиране на осредненото измерване
    Serial.print("АЦП усреднено = ");
    Serial.println(finalAverage);
  }
}
