#ifndef AGS_SENSOR_H
#define AGS_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AGS02MA.h>

class AGSSensor {
public:
    static const unsigned long AGS_READ_INTERVAL = 10000;  // Read every 10 seconds
    
    AGSSensor();
    bool setup();
    void read();
    bool shouldRead();

private:
    static const uint8_t AGS_SDA_PIN = D4;
    static const uint8_t AGS_SCL_PIN = D3;
    
    Adafruit_AGS02MA ags;
    TwoWire wire2;
    unsigned long lastReadTime;
};

#endif