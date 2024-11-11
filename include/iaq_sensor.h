#ifndef IAQ_SENSOR_H
#define IAQ_SENSOR_H

#include <Arduino.h>
#include <Wire.h>

class IAQCoreSensor {
public:
    // Constructor
    IAQCoreSensor();
    
    // Public methods
    bool begin(int sda_pin, int scl_pin);
    void read();
    void printMeasurements();
    
    // Getter methods
    uint16_t getECO2() const { return eco2; }
    uint16_t getTVOC() const { return tvoc; }
    uint32_t getResistance() const { return resistance; }
    uint16_t getStatus() const { return status; }

private:
    // Constants
    static const uint8_t IAQCORE_I2CADDR = 0x5A;  // 7-bit I2C slave address of the iAQ-Core
    static const uint8_t IAQCORE_SIZE = 9;        // Size (in bytes) of the measurement data block 
    
    // Status flags
    static const uint16_t IAQCORE_STAT_OK = 0x0000;     // Data ok
    static const uint16_t IAQCORE_STAT_BUSY = 0x0001;   // Data might be inconsistent
    static const uint16_t IAQCORE_STAT_RUNIN = 0x0010;  // Warm up phase
    static const uint16_t IAQCORE_STAT_ERROR = 0x0080;  // Sensor might be broken
    static const uint16_t IAQCORE_STAT_I2CERR = 0x0100; // I2C transaction error
    
    // Private variables
    uint16_t eco2;
    uint16_t status;
    uint32_t resistance;
    uint16_t tvoc;
    
    // Private methods
    bool beginSensor();
};

#endif // IAQ_SENSOR_H