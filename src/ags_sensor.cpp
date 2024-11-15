#include "ags_sensor.h"

AGSSensor::AGSSensor() : wire2(), lastReadTime(0) {
}

bool AGSSensor::setup() {
    wire2.begin(AGS_SDA_PIN, AGS_SCL_PIN);
    wire2.setClock(20000);
    
    if (!ags.begin(&wire2, 0x1A)) {
        Serial.println("Couldn't find AGS02MA sensor!");
        return false;
    }

    if (ags.getFirmwareVersion() == 0) {
        Serial.println("Could not read AGS02MA firmware!");
        return false;
    }

    Serial.println("AGS02MA sensor initialized!");
    return true;
}

bool AGSSensor::shouldRead() {
    return (millis() - lastReadTime >= AGS_READ_INTERVAL);
}

void AGSSensor::read() {
    if (!shouldRead()) {
        return;
    }
    
    lastReadTime = millis();
    
    wire2.begin(AGS_SDA_PIN, AGS_SCL_PIN);
    wire2.setClock(20000);
    
    uint32_t resistance = ags.getGasResistance();
    delay(50);
    uint32_t tvoc = ags.getTVOC();
    
    if (resistance == 0 || tvoc == 0) {
        Serial.println("\nFailed to read AGS sensor - reinitializing...");
        setup();
        return;
    }
    
    Serial.println("\n=== AGS02MA Readings ===");
    Serial.printf("Gas resistance: %.2f Kohms\n", resistance / 1000.0);
    Serial.printf("TVOC: %d ppb\n", tvoc);
    Serial.println("=====================");
}