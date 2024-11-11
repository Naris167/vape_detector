// src/main.cpp
#include <Arduino.h>
#include "dht_sensor.h"
#include "pms_sensor.h"
#include "ags_sensor.h"
#include "iaq_sensor.h"

// IAQCoreSensor iaqSensor;

// void setup() {
//     Serial.begin(9600);
//     Serial.println("\niAQ-Core sensor test");
    
//     if (!iaqSensor.begin(D2, D1)) {  // SDA = D2, SCL = D1
//         Serial.println("Could not access iAQ-Core sensor!");
//         while (1) delay(1000);
//     }
// }

// void loop() {
//     iaqSensor.read();
//     iaqSensor.printMeasurements();
//     delay(5000);
// }


