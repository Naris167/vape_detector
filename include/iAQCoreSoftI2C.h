// include/iAQCoreSoftI2C.h
#ifndef IAQ_CORE_SOFT_I2C_H
#define IAQ_CORE_SOFT_I2C_H

#include <SoftI2CMaster.h>
#include <iAQCoreTwoWire.h>  // Changed to the correct header

class iAQCoreSoftI2C : public iAQCoreTwoWire 
{
private:
    SoftI2CMaster* softWire;

protected:
    virtual bool read(uint8_t addr, uint8_t* data, size_t len);
    virtual bool write(uint8_t addr, uint8_t* data, size_t len);

public:
    iAQCoreSoftI2C(SoftI2CMaster* wire) : iAQCoreTwoWire(nullptr), softWire(wire) {}
};

#endif