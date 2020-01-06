#include <Adafruit_NeoPixel.h>
#include "images/expanding_brain.h"
#include "modes/ModeWipe.h"
#include "modes/ModeImage.h"
#include "modes/ModeRainbow.h"
#include "modes/ModeTheatreChase.h"

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the LED strip?
#define LED_PIN    15

// How many pixels are on the split in total.
#define LED_COUNT 144

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

Mode** modes;
int num_modes = 0;

void setup() {  
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif

    strip.begin();
    strip.show();
    // Set BRIGHTNESS to about 1/5 (max = 255) 
    // CARE setting this higher, may overdraw the board.
    strip.setBrightness(50); 

    // Setup modes rotation!!!
    modes = new Mode*[20]; num_modes = 8;
    modes[0] = new ModeWipe(strip, strip.Color(255,   0,   0), 50);                 // wipe red @ 50ms/update.
    modes[1] = new ModeWipe(strip, strip.Color(0,   255,   0), 50);                 // wipe green
    modes[2] = new ModeWipe(strip, strip.Color(0,   0,   255), 50);                 // wipe blue
    modes[3] = new ModeTheatreChase(strip, strip.Color(127, 127, 127), 3,  10, 50); // TheatreChase white, every 3rd led, 10 loops, 50ms
    modes[4] = new ModeTheatreChase(strip, strip.Color(127,   0,   0), 5,  10, 70); // red, every 5th led, slower.
    modes[5] = new ModeTheatreChase(strip, strip.Color(0,     0, 127), 10, 10, 30); // blue, every 10th led, faster.
    modes[6] = new ModeRainbow(strip, 3, 10);                                       // Rainbow: 3 loops @ 10ms delay.
    modes[7] = new ModeImage(strip, new ExpandingBrainImg(), 3, 30);                // Image: 3 loops @ 30ms/ line.
}

void loop() {
    for (int m = 0; m < num_modes; m++) {
        modes[m]->Run();
    }
}
