/*
Съществени промени:
- Увеличаване на броя на първоначалните измервания за определяне на офсета.
- Използване на медианно филтриране за определяне на офсета.
- Добавяне на отладъчна информация.
- Промяна на захранващо напрежение на датчик и ОУ на 5V.
*/

#include "ledOnOff.h"
#include <Arduino.h>
#include <algorithm>  // Добавяме библиотека за сортиране (std::sort)
#include "pressure_sensor_03.h"

#define ANALOG_PIN 2   // Използваме GPIO02 за аналогов вход
#define LED_PIN 13     // Използваме GPIO13 за светодиод

//const int adc_values[] = {2062, 2114, 2175, 2218, 2258, 2305, 2332, 2365, 2395, 2430, 2456, 2487, 2514, 2547, 2581, 2603, 2618, 2639, 2657, 2672, 2692, 2703, 2727, 2743, 2774, 2819, 2848, 2878, 2918, 2968, 3022, 3081, 3124, 3177, 3231, 3274, 3335, 3393, 3472, 3543, 3658, 3777, 3875, 3995, 4075};
//const float pressure_values[] = {-210.0, -191.0, -172.0, -156.0, -144.0, -130.0, -120.0, -110.0, -100.0, -88.0, -80.0, -72.0, -62.0, -52.0, -43.0, -39.0, -34.0, -29.0, -22.0, -17.0, -12.0, -9.0, 0.0, 7.0, 15.0, 27.0, 35.0, 43.0, 52.0, 65.0, 79.0, 91.0, 102.0, 112.0, 123.0, 131.0, 142.0, 153.0, 162.0, 171.0, 181.0, 190.0, 197.0, 205.0, 210.0};

float interpolate(int adc_value);
float roundToQuarter(float value);
int adc_readings[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int current_index = 0;
int zero_offset = 0;
unsigned long last_measurement_time = 0;
int adc_values_length;
int adc_zero_index = 0;

int medianFilter(int* values, int size);
int correction_value;

void setup() {
  Serial.begin(9600);  // Започваме сериен монитор на 9600 бауда
  analogSetAttenuation(ADC_11db); // Настройка на затихването за обхват 0-3.3V
  initLED(LED_PIN);

  adc_values_length = findValuesLength();
  adc_zero_index = findZeroIndex(adc_values_length);

  Serial.println("Инициализация...");

  delay(5000);  // Пауза преди началото на инициализацията

  int offset_measurements[20];  // Съхраняваме повече измервания за по-точен офсет
  for (int i = 0; i < 20; i++) {
    offset_measurements[i] = analogRead(ANALOG_PIN);
    Serial.print("Измерване "); Serial.print(i); Serial.print(": "); Serial.println(offset_measurements[i]);  // Отладъчна информация
    delay(250);  // Измерване на всеки 250 ms
  }

  // Медианно филтриране
  zero_offset = medianFilter(offset_measurements, 20);
//*************
  correction_value = zero_offset - adc_values[adc_zero_index];
//*****************
  Serial.print("Zero Offset ADC Value: ");
  Serial.println(zero_offset);
  Serial.println("Инициализация завършена");
}

void loop() {
  unsigned long current_time = millis();
  if (current_time - last_measurement_time >= 100) {  // Измерване на всеки 100 ms
    last_measurement_time = current_time;

    // Четене на текущото отчитане и добавяне към опашката
    adc_readings[current_index] = analogRead(ANALOG_PIN);
    current_index = (current_index + 1) % 10;  // Променяме индекса за следващото отчитане

    // Усредняване на последните 10 отчитания
    int sum = 0;
    for (int i = 0; i < 10; i++) {
      sum += adc_readings[i];
    }
    int average_adc_value = sum / 10 - correction_value;

    // Изместване на усреднената стойност с нулевия офсет
    //average_adc_value -= zero_offset;

    // Принтиране на усреднената стойност на АЦП
    Serial.print("АЦП (усреднено) = ");
    Serial.print(average_adc_value - zero_offset + correction_value);
    //Serial.print(average_adc_value);

    if (average_adc_value < adc_values[0] || average_adc_value > adc_values[adc_values_length]) {
      Serial.println(" => Излиза от обхват");
    } else {
      float pressure_mmH2O = interpolate(average_adc_value);
      pressure_mmH2O = roundToQuarter(pressure_mmH2O);

      Serial.print(", p=");
      Serial.print(pressure_mmH2O, 1);  // Принтиране с точност до 0.1 mmH2O
      Serial.println(" mmH2O");
    }
  }

  ledOn(LED_PIN);
  delay(1000);  // Закъснение от 1 секунда
  ledOff(LED_PIN);
  delay(1000);  // Закъснение от 1 секунда
}

// Разпределение на пиновете:
//J5
// 02_+5.5v
// 12_IO02 (аналогов вход)
// 22_IO23
// 34_IO35
//J6
// 06_GND
// 16_IO13 (светодиод)
// 26_IO5

float interpolate(int adc_value) {
  for (int i = 0; i < adc_values_length; i++) {
    if (adc_value >= adc_values[i] && adc_value <= adc_values[i + 1]) {
      float slope = (pressure_values[i + 1] - pressure_values[i]) / (adc_values[i + 1] - adc_values[i]);
      return pressure_values[i] + slope * (adc_value - adc_values[i]);
    }
  }
  return 0; // В случай на грешка (не трябва да се стига до тук)
}

float roundToQuarter(float value) {
  return round(value * 10) / 10.0;
}

int medianFilter(int* values, int size) {
  std::sort(values, values + size);  // Сортиране на масива
  return values[size / 2];  // Връща медианата
}
