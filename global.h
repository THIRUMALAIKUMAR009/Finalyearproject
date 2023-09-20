#ifndef GLOBAL_H
#define GLOBAL_H

#define AC_VOLTAGE_PIN 1       // 1 represent the analog first pin A0
#define AC_CURRENT_PIN A5

float power_per_second = 0;
float avg_power_per_hour = 0, consumed_power = 0;
int unit = 0, rx = 2;
char inchar = 'X';

#define power_limit_watts 5


#endif
