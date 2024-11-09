// include/ags_sensor.h
#ifndef AGS_SENSOR_H
#define AGS_SENSOR_H

#include <Arduino.h>
#include <Adafruit_AGS02MA.h>

#define AGS_READ_INTERVAL 10000  // Read every 2 seconds

void setupAGS();
void readAGS();

#endif