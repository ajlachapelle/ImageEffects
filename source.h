// Alex LaChapelle
// CS 330 Project 3E

#ifndef _source_h
#define _source_h

#include <image.h>

class Source
{
public:
    Source(void);

    Image* GetOutput(void);

    virtual void Update(void); 

    virtual const char* SourceName(void) = 0;

protected:
    virtual void Execute(void) = 0; 

    Image img;
};

#endif

