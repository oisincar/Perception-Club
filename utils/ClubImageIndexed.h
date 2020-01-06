#ifndef CLUBIMAGEINDEXED_H
#define CLUBIMAGEINDEXED_H

#include "ClubImage.h"

// NOTE: Currently defaults to 16 bit indexed colour.
class ClubImageIndexed : public ClubImage {
public:
    ClubImageIndexed(const uint8_t *key, const uint8_t *img, const int w, const int h) {
        _key = key;
        _img = img;
        _width = w;
        _height = h;
    }

    uint32_t Get(int x, int y) {
        if (x < 0 || x >= _width || y < 0 || y >= _height) {
            // TODO: PRint warning!
        }

        // Image width in bytes, rounding up to whole byte.
        uint32_t w = (_width+1) >> 1; /*E.g. img_w = 13 -> w = 6 + 1 (bytes)*/
        // Byte index of first pixel. x is divided by 2.
        uint32_t pos = w*y + (x >> 1);
        //       subx = x is even ? 0 : 4;
        uint32_t subx = 4 - ((x & 0x1) * 4); // bit index within the byte.

        // Grab relevent byte
        uint32_t col_map = _img[pos];
        // Bitshift and mask. This is now the index to lookup.
        uint32_t col_ix = ((col_map >> subx) & 0xF);
        // Since there are 4 bytes per colour, bump up and...
        col_ix = col_ix * 4;
        // grab r/g/b channels separately.
        uint8_t colB = _key[col_ix]; 
        uint8_t colG = _key[col_ix+1];
        uint8_t colR = _key[col_ix+2];

        // TODO: Doublecheck this is the correct byte order.
        return ((uint32_t)colR << 16) | ((uint32_t)colG << 8) | (colB);
    }

    int GetWidth() { return _width; }
    int GetHeight() { return _height; }

protected:
    const uint8_t *_key, *_img;
    int _width, _height;
};

#endif // CLUBIMAGEINDEXED_H
