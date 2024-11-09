// src/ags_sensor.cpp
#include "ags_sensor.h"

Adafruit_AGS02MA ags;
unsigned long lastAGSReadTime = 0;

void setupAGS() {
    // Set I2C clock to 20KHz (20000)
    Wire.setClock(20000);
    
    if (!ags.begin(&Wire, 0x1A)) {
        Serial.println("Couldn't find AGS02MA sensor!");
        return;
    }

    if (ags.getFirmwareVersion() == 0) {
        Serial.println("Could not read AGS02MA firmware!");
        return;
    }

    Serial.println("AGS02MA sensor initialized!");
}

void readAGS() {
    if (millis() - lastAGSReadTime < AGS_READ_INTERVAL) {
        return;
    }
    
    lastAGSReadTime = millis();

    uint32_t resistance = ags.getGasResistance();
    uint32_t tvoc = ags.getTVOC();
    
    Serial.println("\n=== AGS02MA Readings ===");
    
    if (resistance == 0) {
        Serial.println("Failed to read gas resistance!");
    } else {
        float kohm = resistance / 1000.0;
        Serial.printf("Gas resistance: %.2f Kohms\n", kohm);
    }

    if (tvoc == 0) {
        Serial.println("Failed to read TVOC!");
    } else {
        Serial.printf("TVOC: %d ppb\n", tvoc);
    }
    
    Serial.println("=====================\n");
}