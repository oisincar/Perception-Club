#ifndef CLUBIMAGE_H
#define CLUBIMAGE_H

// Interface for all club images.
// You can add your own as long as it inherits from this!
class ClubImage {
public:
    // Note image is read 'vertically', so when stored in memory
    // rotate so the image's width divides the number of pixels in
    // your club.
    virtual uint32_t Get(int x, int y) = 0;
    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
};

#endif // CLUBIMAGE_H
