#ifndef MODEWIPE_H
#define MODEWIPE_H

#include <Adafruit_NeoPixel.h>
#include "Mode.h"

class ModeWipe : public Mode {
private:
    uint32_t _colour;
    int _delay;
public:
    ModeWipe(Adafruit_NeoPixel& strip, uint32_t colour, int delay) :
        Mode(strip), _colour(colour), _delay(delay) {}

    // Adapted from neopixel sample code.
    void Run() {
        for(int i = 0; i < _strip.numPixels()/2; i++) {
            _strip.setPixelColor(i, _colour);
            _strip.setPixelColor(_strip.numPixels() - i, _colour);
            _strip.show();
            delay(_delay);
        }
    }
};

#endif // MODEWIPE_H
