#ifndef MODETHEATRECHASE_H
#define MODETHEATRECHASE_H

#include <Adafruit_NeoPixel.h>
#include "Mode.h"

class ModeTheatreChase : public Mode {
private:
    uint32_t _colour;
    int _loops, _delay, _spacing;
public:
    ModeTheatreChase(Adafruit_NeoPixel& strip, uint32_t colour, int spacing, int loops, int delay) :
        Mode(strip), _colour(colour), _spacing(spacing), _loops(loops), _delay(delay) {}

    // Adapted from neopixel sample code.
    void Run() {
        for(int i = 0; i < _loops; i++) {  // Repeat 10 times...
            for(int x = 0; x < _spacing; x++) { //  'x' counts from 0 to 2...
                _strip.clear();

                for(int y = x; y < _strip.numPixels()/2; y += _spacing) {
                    _strip.setPixelColor(y, _colour);
                    _strip.setPixelColor(_strip.numPixels() - y, _colour);
                }
                _strip.show(); // Update strip with new contents
                delay(_delay);  // Pause for a moment
            }
        }}
};

#endif // MODETHEATRECHASE_H
