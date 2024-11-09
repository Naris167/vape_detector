// src/pms_sensor.cpp
#include "pms_sensor.h"

SoftwareSerial pmsSerial(PMS_RX, PMS_TX);
unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;
unsigned long lastPMSReadTime = 0;  // Track last reading time

void setupPMS() {
    pmsSerial.begin(9600);
    
    // Send wake-up command
    uint8_t wakeup[] = {0x42, 0x4D, 0xE4, 0x00, 0x01, 0x01, 0x74}; 
    pmsSerial.write(wakeup, sizeof(wakeup));
    
    Serial.println("PMS3003 waking up...");
    delay(1000);
}

void readPMS() {
    // Only read if interval has passed
    if (millis() - lastPMSReadTime < PMS_READ_INTERVAL) {
        return;
    }
    
    int index = 0;
    char value;
    char previousValue;
    bool dataReceived = false;

    while (pmsSerial.available()) {
        value = pmsSerial.read();
        
        // Check for the data header
        if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d)) {
            break;
        }

        // Process sensor data bytes
        if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14) {
            previousValue = value;
        }
        else if (index == 5) {
            pm1 = 256 * previousValue + value;
            dataReceived = true;
        }
        else if (index == 7) {
            pm2_5 = 256 * previousValue + value;
        }
        else if (index == 9) {
            pm10 = 256 * previousValue + value;
        }
        else if (index > 15) {
            break;
        }
        index++;
    }

    // Clear any extra bytes in the buffer
    while(pmsSerial.available()) pmsSerial.read();

    // Update last read time
    lastPMSReadTime = millis();

    // Print readings if data was received
    if (dataReceived) {
        Serial.println("\n=== PMS3003 Readings ===");
        Serial.printf("PM 1.0: %d ug/m3\n", pm1);
        Serial.printf("PM 2.5: %d ug/m3\n", pm2_5);
        Serial.printf("PM 10.0: %d ug/m3\n", pm10);
        Serial.println("=====================\n");
    }
}