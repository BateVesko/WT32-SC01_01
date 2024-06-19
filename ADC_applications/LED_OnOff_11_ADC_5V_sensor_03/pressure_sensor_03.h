#ifndef PRESSURE_SENSOR_3_H
#define PRESSURE_SENSOR_3_H

const int adc_values[] = {
  769, 882, 992, 1128, 1248, 1356, 1472, 1597, 1707, 1829, 
  1942, 2069, 2181, 2294, 2411, 2521, 2646, 2771, 2894, 3006, 
  3149, 3315, 3485, 3703, 3924
};

const float pressure_values[] = {
  200.0, 190.0, 180.0, 170.0, 160.0, 150.0, 140.0, 130.0, 
  120.0, 110.0, 100.0, 90.0, 80.0, 70.0, 60.0, 50.0, 40.0, 
  30.0, 20.0, 10.0, 0.0, -10.0, -20.0, -30.0, -40.0
};

int findValuesLength() {
  return sizeof(adc_values) / sizeof(adc_values[0]);
}

int findZeroIndex(int length) {
  for (int i = 0; i < length; i++) {
    if (pressure_values[i] == 0.0) {
      return i;
    }
  }
  return -1; // В случай на грешка
}

#endif // PRESSURE_SENSOR_3_H
