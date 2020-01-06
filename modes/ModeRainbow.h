#ifndef MODERAINBOW_H
#define MODERAINBOW_H

#include <Adafruit_NeoPixel.h>
#include "Mode.h"

class ModeRainbow : public Mode {
private:
    int _loops, _delay;
public:
    ModeRainbow(Adafruit_NeoPixel& strip, int loops, int delay) :
        Mode(strip), _loops(loops), _delay(delay) {}

    // Adapted from neopixel sample code.
    void Run() {
        for (int i = 0; i < _loops; i++) {
            for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
                for(int i = 0; i < _strip.numPixels()/2; i++) { // For each pixel in strip...
                    // Offset pixel hue by an amount to make one full revolution of the
                    // color wheel (range of 65536) along the length of the strip
                    // (strip.numPixels() steps):
                    int pixelHue = firstPixelHue + (i * 65536L / _strip.numPixels()*2);
                    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
                    // optionally add saturation and value (brightness) (each 0 to 255).
                    // Here we're using just the single-argument hue variant. The result
                    // is passed through strip.gamma32() to provide 'truer' colors
                    // before assigning to each pixel:

                    _strip.setPixelColor(i, _strip.gamma32(_strip.ColorHSV(pixelHue)));
                    _strip.setPixelColor(_strip.numPixels() - i, _strip.gamma32(_strip.ColorHSV(pixelHue)));
                }
                _strip.show(); // Update strip with new contents
                delay(_delay);  // Pause for a moment
            }
        }
    }
};

#endif // MODERAINBOW_H
