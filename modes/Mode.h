#ifndef MODE_H
#define MODE_H

#include <Adafruit_NeoPixel.h>

// Interface for all modes. Simply defines a 'run' function, which can hold control
// as long as the mode is running.
class Mode {
protected:
    Adafruit_NeoPixel& _strip;

public:
    Mode(Adafruit_NeoPixel& strip) : _strip(strip) {}
    virtual void Run() = 0;
};

#endif // MODE_H
