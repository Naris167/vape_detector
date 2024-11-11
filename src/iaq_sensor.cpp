#include "iaq_sensor.h"

IAQCoreSensor::IAQCoreSensor() : 
    eco2(0), status(0), resistance(0), tvoc(0) {
}

bool IAQCoreSensor::begin(int sda_pin, int scl_pin) {
    Wire.begin(sda_pin, scl_pin);
    Wire.setClockStretchLimit(500);
    return beginSensor();
}

bool IAQCoreSensor::beginSensor() {
    // Check if device is accessible
    read();
    if (status & IAQCORE_STAT_I2CERR) {
        return false;
    }
    // Check if the wire library waits long enough for clock stretching
    if ((resistance >> 24) == 0xFF) {
        return false;
    }
    return true;
}

void IAQCoreSensor::read() {
    // Request data from sensor
    int num = Wire.requestFrom((uint8_t)IAQCORE_I2CADDR, (size_t)IAQCORE_SIZE);
    
    // Read data into buffer
    uint8_t buf[IAQCORE_SIZE];
    for (int i = 0; i < IAQCORE_SIZE; i++) {
        buf[i] = Wire.read();
    }
    
    // Parse the data
    eco2 = (buf[0] << 8) | buf[1];
    status = (num == IAQCORE_SIZE ? 0 : IAQCORE_STAT_I2CERR) | buf[2];
    resistance = ((uint32_t)buf[3] << 24) | ((uint32_t)buf[4] << 16) | 
                 ((uint32_t)buf[5] << 8) | buf[6];
    tvoc = (buf[7] << 8) | buf[8];
}

void IAQCoreSensor::printMeasurements() {
    // Print status
    Serial.print("Status: ");
    if (status == IAQCORE_STAT_OK) Serial.println("OK");
    else {
        if (status & IAQCORE_STAT_I2CERR) Serial.println("I2C ERROR");
        if (status & IAQCORE_STAT_BUSY)   Serial.println("BUSY");
        if (status & IAQCORE_STAT_RUNIN)  Serial.println("WARMING UP");
        if (status & IAQCORE_STAT_ERROR)  Serial.println("ERROR");
    }
    
    // Print measurements
    Serial.print("CO2 equivalent: "); Serial.print(eco2); Serial.println(" ppm");
    Serial.print("TVOC: "); Serial.print(tvoc); Serial.println(" ppb");
    Serial.print("Resistance: "); Serial.println(resistance);
    Serial.println();
}