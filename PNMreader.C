// Alex LaChapelle
// CS 330 Project 3E

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <image.h>
#include <PNMreader.h>
#include <source.h>

PNMreader::PNMreader(const char* filename)
{
    this->filename = strdup(filename);
}

PNMreader::~PNMreader(void)
{
    free(this->filename);
}

void PNMreader::Execute(void)
{
    FILE* f_in = fopen(filename, "r");
    char magicNum[128];
    int width, height, maxval;
    fscanf(f_in, "%s\n%d %d\n%d\n", 
           magicNum, &width, &height, &maxval);

    // Allocate pixels and read in binary data
    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));
    fread(pixels, width * height, sizeof(Pixel), f_in);
    fclose(f_in);

    GetOutput()->SetImage(width, height, pixels);
}

