#ifndef IAQ_SENSOR_H
#define IAQ_SENSOR_H

#include <Arduino.h>
#include <Wire.h>

class IAQCoreSensor {
public:
    static const unsigned long IAQ_READ_INTERVAL = 5000;
    
    IAQCoreSensor();
    bool begin(int sda_pin, int scl_pin);
    void read();
    bool shouldRead();

private:
    static const uint8_t IAQCORE_I2CADDR = 0x5A;
    static const uint8_t IAQCORE_SIZE = 9;
    
    static const uint16_t IAQCORE_STAT_OK = 0x0000;
    static const uint16_t IAQCORE_STAT_BUSY = 0x0001;
    static const uint16_t IAQCORE_STAT_RUNIN = 0x0010;
    static const uint16_t IAQCORE_STAT_ERROR = 0x0080;
    static const uint16_t IAQCORE_STAT_I2CERR = 0x0100;
    
    uint16_t eco2;
    uint16_t status;
    uint32_t resistance;
    uint16_t tvoc;
    unsigned long lastReadTime;
    bool isInitialized;
    
    bool checkConnection();  // New method to check sensor connection
};

#endif