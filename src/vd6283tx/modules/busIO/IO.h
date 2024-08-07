#ifndef __IO__
#define __IO__

#include <Arduino.h>
#include <Wire.h>

class BusIO
{
  private:
    // I2C instance
    TwoWire *_i2cPort;

    // Sensor address
    uint8_t _address;

    // I2C maximum packet size
    uint8_t wireMaxPacketSize = 32;

  public:
    // Default constructor
    BusIO(){};

    // Begin two wire interface
    bool begin(byte address, TwoWire &wirePort);

    // Return true if we get a reply from the I2C device.
    bool isConnected();

    // Read a single byte from a register.
    uint8_t readSingleByte(uint8_t registerAddress);

    // Write a single byte into a register.
    uint8_t writeSingleByte(uint8_t registerAddress, uint8_t value);

    // Read multiple bytes from a register into buffer byte array.
    uint8_t readMultipleBytes(uint8_t registerAddress, uint8_t *buffer, uint16_t bufferSize);

    // Write multiple bytes to register from buffer byte array.
    uint8_t writeMultipleBytes(uint8_t registerAddress, uint8_t *buffer, uint16_t bufferSize);

    // Get I2C maximum packet size
    uint8_t getMaxPacketSize() { return wireMaxPacketSize; }

    // Set I2C maximum packet size
    void setMaxPacketSize(uint8_t newSize) { wireMaxPacketSize = newSize; }
};

#endif
