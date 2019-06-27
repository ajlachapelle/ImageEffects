// Alex LaChapelle
// CS 330 Project 3E

#include <stdio.h>
#include <image.h>
#include <PNMwriter.h>
#include <sink.h>

void PNMwriter::Write(const char* filename)
{
    const Image& img = *GetInput();
    FILE* f_out = fopen(filename, "w");
    int width = img.GetWidth();
    int height = img.GetHeight();
    fprintf(f_out, "P6\n%d %d\n255\n", width, height);
    fwrite(img.GetPixels(), width * height, sizeof(Pixel), f_out);
    fclose(f_out); 
}

