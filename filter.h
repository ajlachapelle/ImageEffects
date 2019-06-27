// Alex LaChapelle
// CS 330 Project 3E

#ifndef _filter_h
#define _filter_h

#include <image.h>
#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink
{
public:
    Filter(void) {}
    void Update(void);

    virtual const char* FilterName(void) = 0;
    const char* SourceName(void) {return FilterName();}
    const char* SinkName(void) {return FilterName();}


    void CheckNull(const Image* pImg);
    void CheckWidth(int width1, int width2);
    void CheckHeight(int height1, int height2);
};


class Color : public Source
{
public:
    Color(int width, int height, unsigned char r, unsigned char g, unsigned char b);
    virtual ~Color(void);

    const char* SourceName(void) {return "Color";}
    void Execute(void);
};


class CheckSum : public Sink
{
public:
    CheckSum(void) {}

    const char* SinkName(void) {return "CheckSum";}
    void OutputCheckSum(const char* filename);
};


class Shrinker : public Filter
{
public:
    Shrinker(void) {}

    const char* FilterName(void) {return "Shrinker";}
    void Execute(void);
};


class LRCombine : public Filter
{
public:
    LRCombine(void) {}

    const char* FilterName(void) {return "LRCombine";}
    void Execute(void);
};


class TBCombine : public Filter
{
public:
    TBCombine(void) {}

    const char* FilterName(void) {return "TBCombine";}
    void Execute(void);
};


class Blender : public Filter
{
public:
    Blender(void);

    void SetFactor(double f);

    const char* FilterName(void) {return "Blender";}
    void Execute(void);

private:
    double factor;
};


class Mirror : public Filter
{
public:
    Mirror (void) {}

    const char* FilterName(void) {return "Mirror";}
    void Execute(void);
};


class Rotate : public Filter
{
public:
    Rotate(void) {}

    const char* FilterName(void) {return "Rotate";}
    void Execute(void);
};


class Subtract: public Filter
{
public:
    Subtract(void) {}

    const char* FilterName(void) {return "Subtract";}
    void Execute(void);
};


class Grayscale: public Filter
{
public:
    Grayscale(void) {}

    const char* FilterName(void) {return "Grayscale";}
    void Execute(void);
};


class Blur : public Filter
{
public:
    Blur(void) {}

    const char* FilterName(void) {return "Blur";}
    void Execute(void);
};

#endif

