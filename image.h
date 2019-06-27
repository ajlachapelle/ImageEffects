// Alex LaChapelle
// CS 330 Project 3E

#ifndef _image_h
#define _image_h

class Source;

class Pixel
{
public:
    void PixelBlend(const Pixel& input1, const Pixel& input2, double factor);
    void ToGrayscale(const Pixel& input);
    void Subtract(const Pixel& input1, const Pixel& input2);
    void Average(const Pixel& p1, const Pixel& p2, const Pixel& p3,
                 const Pixel& p4, const Pixel& p5,
                 const Pixel& p6, const Pixel& p7, const Pixel& p8);

    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class Image
{
public:
    Image(void);
    Image(int w, int h, Pixel* p);
    Image(Image& img);
    virtual ~Image(void);

    void SetImage(int w, int h, Pixel* p);
    void SetSource(Source* src) {source = src;}

    int GetWidth(void) const {return width;}
    int GetHeight(void) const {return height;}
    const Pixel* GetPixels(void) const {return pixels;}
    int GetSize(void) const {return width*height*sizeof(Pixel);}

    void Update(void);

private:
    int width;
    int height;
    Pixel* pixels;
    Source* source;
};

#endif

