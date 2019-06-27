// Alex LaChapelle
// CS 330 Project 3E

#ifndef _PNMreader_h
#define _PNMreader_h

#include <source.h>

class PNMreader : public Source
{
public:
    PNMreader(const char* filename);
    virtual ~PNMreader(void);

    const char* SourceName(void) {return "PNMreader";}
    void Execute(void);

private:
    char* filename;
};

#endif

