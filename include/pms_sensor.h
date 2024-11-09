// include/pms_sensor.h
#ifndef PMS_SENSOR_H
#define PMS_SENSOR_H

#include <Arduino.h>
#include <SoftwareSerial.h>

// GPIO pins: D2 = GPIO4, D1 = GPIO5
#define PMS_RX 14  // D5, connect to PMS TXD
#define PMS_TX 12  // D6, connect to PMS RXD
#define PMS_READ_INTERVAL 10000  // Read every 2 seconds

void setupPMS();
void readPMS();

#endif