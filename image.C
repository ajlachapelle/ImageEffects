// Alex LaChapelle
// CS 330 Project 3E

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <image.h>
#include <source.h>

Image::Image(void)
{
    width = 0;
    height = 0;
    pixels = NULL;
    source = NULL;
}

Image::Image(int w, int h, Pixel* p)
{
    width = w;
    height = h;
    pixels = p;
}

Image::Image(Image& input)
{
    width = input.width;
    height = input.height;
    int size = width * height * sizeof(Pixel);
    pixels = (Pixel*)malloc(size);
    memcpy(pixels, input.pixels, size);
}

Image::~Image(void)
{
    free(pixels);
}

void Image::SetImage(int w, int h, Pixel* p)
{
    width = w;
    height = h;
    free(pixels);
    pixels = p;
}

void Image::Update(void)
{
    // If source is not null, update source
    if (source)
        source->Update();
}

void Pixel::PixelBlend(const Pixel& input1, const Pixel& input2, double factor)
{
    double factor2 = 1-factor;
    r = (input1.r*factor) + (input2.r*factor2);
    g = (input1.g*factor) + (input2.g*factor2);
    b = (input1.b*factor) + (input2.b*factor2);
}

void Pixel::ToGrayscale(const Pixel& input)
{
    r = g = b = int(input.r/5) + int(input.g/2) + int(input.b/4);
}

void Pixel::Subtract(const Pixel& input1, const Pixel& input2)
{
    r = input1.r - input2.r;
    g = input1.g - input2.g;
    b = input1.b - input2.b;
}

void Pixel::Average(const Pixel& p1, const Pixel& p2, const Pixel& p3,
                    const Pixel& p4, const Pixel& p5,
                    const Pixel& p6, const Pixel& p7, const Pixel& p8)
{
    int n;
    n = int(p1.r/8) + int(p2.r/8) + int(p3.r/8) + int(p4.r/8)
      + int(p5.r/8) + int(p6.r/8) + int(p7.r/8) + int(p8.r/8);
    r = n % 256;

    n = int(p1.g/8) + int(p2.g/8) + int(p3.g/8) + int(p4.g/8)
      + int(p5.g/8) + int(p6.g/8) + int(p7.g/8) + int(p8.g/8);
    g = n % 256;

    n = int(p1.b/8) + int(p2.b/8) + int(p3.b/8) + int(p4.b/8)
      + int(p5.b/8) + int(p6.b/8) + int(p7.b/8) + int(p8.b/8);
    b = n % 256;
}

