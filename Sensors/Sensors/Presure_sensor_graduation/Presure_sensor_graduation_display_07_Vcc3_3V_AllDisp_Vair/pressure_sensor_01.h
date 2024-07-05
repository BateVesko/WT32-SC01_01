#ifndef PRESSURE_SENSOR_01_H
#define PRESSURE_SENSOR_01_H

const int adc_values[] = {
  2062, 2114, 2175, 2218, 2258, 2305, 2332, 2365, 2395, 2430, 2456, 2487, 2514, 2547, 2581, 2603, 
  2618, 2639, 2657, 2672, 2692, 2703, 2727, 2743, 2774, 2819, 2848, 2878, 2918, 2968, 3022, 3081, 
  3124, 3177, 3231, 3274, 3335, 3393, 3472, 3543, 3658, 3777, 3875, 3995, 4075
};

const float pressure_values[] = {
  -210.0, -191.0, -172.0, -156.0, -144.0, -130.0, -120.0, -110.0, -100.0, -88.0, -80.0, -72.0, 
  -62.0, -52.0, -43.0, -39.0, -34.0, -29.0, -22.0, -17.0, -12.0, -9.0, 0.0, 7.0, 15.0, 27.0, 
  35.0, 43.0, 52.0, 65.0, 79.0, 91.0, 102.0, 112.0, 123.0, 131.0, 142.0, 153.0, 162.0, 171.0, 
  181.0, 190.0, 197.0, 205.0, 210.0
};

//const int adc_values_length = sizeof(adc_values) / sizeof(adc_values[0]);
const int adc_values_length = 44;
const int adc_zero_index = 22;

#endif // PRESSURE_SENSOR_01_H
