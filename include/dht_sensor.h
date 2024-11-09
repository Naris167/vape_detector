// include/dht_sensor.h
#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

// Pin and sensor configuration
#define DHTPIN D3        // Data pin
#define DHTTYPE DHT22    // DHT22 (AM2302)
#define READ_INTERVAL 10000 // Reading interval in milliseconds

void setupDHT();
void readAndDisplayDHT();

#endif