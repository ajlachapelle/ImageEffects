// Alex LaChapelle
// CS 330 Project 3E

#ifndef _PNMwriter_h
#define _PNMwriter_h

#include <sink.h>

class PNMwriter : public Sink 
{
public:
    PNMwriter(void) {}

    const char* SinkName(void) {return "PNMwriter";}
    void Write(const char* filename);
};

#endif

