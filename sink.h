// Alex LaChapelle
// CS 330 Project 3E

#ifndef _sink_h
#define _sink_h

#include <image.h>

class Sink
{
public:
    Sink(void);

    void SetInput(Image* img) {img1 = img;}
    void SetInput2(Image* img) {img2 = img;}

    const Image* GetInput(void) {return img1;}
    const Image* GetInput2(void) {return img2;}

    virtual const char* SinkName(void) = 0;

protected:
    const Image* img1;
    const Image* img2;
};

#endif

