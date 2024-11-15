#include "iaq_sensor.h"

IAQCoreSensor::IAQCoreSensor() : 
    eco2(0), status(0), resistance(0), tvoc(0), 
    lastReadTime(0), isInitialized(false) {
}

bool IAQCoreSensor::checkConnection() {
    Wire.beginTransmission(IAQCORE_I2CADDR);
    uint8_t error = Wire.endTransmission();
    Serial.print("Connection check result: ");
    Serial.println(error);
    return (error == 0);
}

bool IAQCoreSensor::begin(int sda_pin, int scl_pin) {
    Serial.println("Initializing iAQ-Core sensor...");
    
    Wire.begin(sda_pin, scl_pin);
    Wire.setClockStretchLimit(500);
    Wire.setClock(100000);
    
    delay(100);  // Give sensor time to stabilize
    
    if (!checkConnection()) {
        Serial.println("Could not find iAQ-Core sensor!");
        return false;
    }

    // Try to get initial reading
    Wire.requestFrom((uint8_t)IAQCORE_I2CADDR, (size_t)IAQCORE_SIZE);
    if (Wire.available() == IAQCORE_SIZE) {
        Serial.println("Initial reading successful");
        isInitialized = true;
    } else {
        Serial.println("Failed to get initial reading");
        return false;
    }

    Serial.println("iAQ-Core sensor initialized successfully!");
    return true;
}

bool IAQCoreSensor::shouldRead() {
    unsigned long currentTime = millis();
    bool shouldReadNow = isInitialized && (currentTime - lastReadTime >= IAQ_READ_INTERVAL);
    
    if (!isInitialized) {
        Serial.println("Sensor not initialized!");
    }
    
    return shouldReadNow;
}

void IAQCoreSensor::read() {
    if (!shouldRead()) {
        return;
    }

    Serial.println("Starting iAQ read...");
    
    // Reinitialize I2C for this sensor
    Wire.begin(D2, D1);
    Wire.setClockStretchLimit(500);
    Wire.setClock(100000);
    
    delay(10);  // Small delay after reinitialization
    
    // Mark time at start of reading
    lastReadTime = millis();
    
    Wire.beginTransmission(IAQCORE_I2CADDR);
    if (Wire.endTransmission() != 0) {
        Serial.println("Failed to communicate with sensor");
        status |= IAQCORE_STAT_I2CERR;
        return;
    }

    int num = Wire.requestFrom((uint8_t)IAQCORE_I2CADDR, (size_t)IAQCORE_SIZE);
    
    if (num != IAQCORE_SIZE) {
        Serial.print("Incorrect byte count. Expected: ");
        Serial.print(IAQCORE_SIZE);
        Serial.print(" Got: ");
        Serial.println(num);
        status |= IAQCORE_STAT_I2CERR;
        return;
    }

    uint8_t buf[IAQCORE_SIZE];
    for (int i = 0; i < IAQCORE_SIZE; i++) {
        buf[i] = Wire.read();
    }
    
    eco2 = (buf[0] << 8) | buf[1];
    status = (num == IAQCORE_SIZE ? 0 : IAQCORE_STAT_I2CERR) | buf[2];
    resistance = ((uint32_t)buf[3] << 24) | ((uint32_t)buf[4] << 16) | 
                 ((uint32_t)buf[5] << 8) | buf[6];
    tvoc = (buf[7] << 8) | buf[8];
    
    Serial.println("\n=== iAQ Sensor Readings ===");
    Serial.print("Status: ");
    if (status == IAQCORE_STAT_OK) {
        Serial.println("OK");
    } else {
        if (status & IAQCORE_STAT_I2CERR) Serial.println("I2C ERROR");
        if (status & IAQCORE_STAT_BUSY)   Serial.println("BUSY");
        if (status & IAQCORE_STAT_RUNIN)  Serial.println("WARMING UP");
        if (status & IAQCORE_STAT_ERROR)  Serial.println("ERROR");
    }
    
    Serial.print("CO2 equivalent: "); Serial.print(eco2); Serial.println(" ppm");
    Serial.print("TVOC: "); Serial.print(tvoc); Serial.println(" ppb");
    Serial.print("Resistance: "); Serial.println(resistance);
    Serial.println("=====================");
}