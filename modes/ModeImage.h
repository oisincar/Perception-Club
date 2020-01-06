#ifndef MODEIMAGE_H
#define MODEIMAGE_H

#include <Adafruit_NeoPixel.h>
#include "Mode.h"
//#include "../utils/ClubImage.h"
#include "../images/expanding_brain.h"

class ModeImage : public Mode {
private:
    ExpandingBrainImg* _image;
    uint32_t _loops, _delay;
public:
    // ClubImage
    ModeImage(Adafruit_NeoPixel& strip, ExpandingBrainImg* image, uint32_t loops, uint32_t delay) :
        Mode(strip), _image(image), _loops(loops), _delay(delay) {}

    void Run() {
        // How much the image is to be scaled along the x axis, used later.
        // Note image width must divide the number of leds evenly.
        int scaleFact = 2; //_strip.numPixels() / (2 * _image.GetWidth());

        // Num loops through image
        for (int l = 0; l < _loops; l++) {
            // Each loop top to bottom
            for (int y = 0; y < _image->GetHeight(); y++) {
                // Render slice.
                for (int x = 0; x < IMG_W; x++) {
                    uint32_t colour = _image->Get(x, y);

                    // Scale image to fit the width correctly.
                    // Should fit in twice into the number of pixels in the strip.
                    int img_x = x * scaleFact;

                    // For however much we're scaling the image, we need to set all
                    // of the relevent leds to the same colour.
                    for (int i = 0; i < scaleFact; i++) {
                        _strip.setPixelColor(img_x+i, colour);
                        _strip.setPixelColor(_strip.numPixels() - (img_x+i), colour);
                    }
                }

                _strip.show();
                delay(_delay);
            }
        }
    }
};

#endif // MYMATH_H
