// src/main.cpp
#include <Arduino.h>
#include "dht_sensor.h"
#include "pms_sensor.h"
#include "ags_sensor.h"

void setup() {
    Serial.begin(9600);
    
    // Initialize I2C first for AGS02MA
    Wire.begin();
    
    setupDHT();
    setupPMS();
    setupAGS();
    Serial.println("All sensors initialized!");
}

void loop() {
    readAndDisplayDHT();
    readPMS();
    readAGS();
}