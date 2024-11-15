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


#include <Arduino.h>
#include "iaq_sensor.h"
#include "ags_sensor.h"

IAQCoreSensor iaqSensor;
AGSSensor agsSensor;

void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println("\nDual I2C Sensor Test");
    
    // Initialize iAQ sensor on first I2C bus (D1, D2)
    if (!iaqSensor.begin(D2, D1)) {
        Serial.println("Could not access iAQ-Core sensor!");
        while (1) delay(1000);
    }
    
    delay(100);  // Small delay between initializations
    
    // Initialize AGS sensor on second I2C bus (D3, D4)
    if (!agsSensor.setup()) {
        Serial.println("Could not access AGS sensor!");
        while (1) delay(1000);
    }
}

void loop() {
    // Try to read both sensors every loop
    iaqSensor.read();
    delay(50);  // Small delay between sensors
    agsSensor.read();
    
    // Delay before next cycle
    delay(900);  // Total cycle time around 1 second
}