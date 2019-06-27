// Alex LaChapelle
// CS 330 Project 3F

#include <stdlib.h>
#include <string.h>
#include <filter.h>
#include <source.h>
#include <sink.h>
#include <logging.h>

void Filter::Update(void)
{
    // Update non-null images, then update source
    Logger::LogEvent(FilterName(), "about to update input1");
    ((Image*)img1)->Update();
    Logger::LogEvent(FilterName(), "done updating input1");

    if (img2)
    {
       Logger::LogEvent(FilterName(), "about to update input2");
       ((Image*)img2)->Update();
       Logger::LogEvent(FilterName(), "done updating input2");
    }
    Source::Update();
}

void Filter::CheckNull(const Image* pImg)
{
    if (pImg == NULL)
    {
        DataFlowException e(FilterName(), "Null image pointer");
        throw e;
    }
}

void Filter::CheckWidth(int width1, int width2)
{
    if (width1 != width2)
    {
        char msg[1024];
        sprintf(msg, "Widths must match: %d, %d", width1, width2);
        DataFlowException e(FilterName(), msg);
        throw e;
    }
}

void Filter::CheckHeight(int height1, int height2)
{
    if (height1 != height2)
    {
        char msg[1024];
        sprintf(msg, "heights must match: %d, %d", height1, height2);
        DataFlowException e(FilterName(), msg);
        throw e;
    }
}


void CheckSum::OutputCheckSum(const char* filename)
{
    //CheckNull(GetInput());

    const Image& input = *GetInput();

    int width = input.GetWidth()/2;
    int height = input.GetHeight()/2;
    const Pixel* inPixels = input.GetPixels();
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    for (int row=0, k=0; row<height; ++row)
        for (int col=0; col<width; ++col, ++k)
        {
            r += inPixels[k].r;
            g += inPixels[k].g;
            b += inPixels[k].b;
        }

    FILE* fp = fopen(filename, "w");
    fprintf(fp, "CHECKSUM: %d, %d, %d\n", r, g, b);
    fclose(fp);
}


void Shrinker::Execute(void)
{
    CheckNull(GetInput());

    const Image& input = *GetInput();

    int width = input.GetWidth()/2;
    int height = input.GetHeight()/2;
    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    const Pixel* inPixels = input.GetPixels();
    for (int row=0, k=0; row<height; ++row)
        for (int col=0; col<width; ++col, ++k)
            pixels[k] = inPixels[2*(row*input.GetWidth()+col)];

    GetOutput()->SetImage(width, height, pixels);
}


void LRCombine::Execute(void)
{
    CheckNull(GetInput());
    CheckNull(GetInput2());

    const Image& leftInput = *GetInput();
    const Image& rightInput = *GetInput2();

    int width = leftInput.GetWidth() + rightInput.GetWidth();
    int height = leftInput.GetHeight();

    CheckHeight(height, rightInput.GetHeight());

    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    // Copy rows from input arrays, alternating between left and right inputs
    for (int row=0; row<height; ++row)
    {
        memcpy(pixels + row*width, 
               leftInput.GetPixels() + row*leftInput.GetWidth(), 
               leftInput.GetWidth() * sizeof(Pixel)); 
        memcpy(pixels + row*width + leftInput.GetWidth(), 
               rightInput.GetPixels() + row*rightInput.GetWidth(), 
               rightInput.GetWidth() * sizeof(Pixel)); 
    }

    GetOutput()->SetImage(width, height, pixels);
}


void TBCombine::Execute(void)
{
    CheckNull(GetInput());
    CheckNull(GetInput2());

    const Image& topInput = *GetInput();
    const Image& bottomInput = *GetInput2();

    int width = topInput.GetWidth();
    int height = topInput.GetHeight() + bottomInput.GetHeight();

    CheckWidth(width, bottomInput.GetWidth());

    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    int size = topInput.GetSize();
    memcpy(pixels, topInput.GetPixels(), size);
    memcpy((char*)pixels + size, bottomInput.GetPixels(), bottomInput.GetSize());

    GetOutput()->SetImage(width, height, pixels);
}


Blender::Blender(void)
{
    factor = -1.0; // Initialize factor to invalid value
}

void Blender::SetFactor(double f)
{
    factor = f;
}

void Blender::Execute(void)
{
    CheckNull(GetInput());
    CheckNull(GetInput2());

    const Image& input1 = *GetInput();
    const Image& input2 = *GetInput2();

    int width = input1.GetWidth();
    int height = input1.GetHeight();

    CheckWidth(width, input2.GetWidth());
    CheckHeight(height, input2.GetHeight());

    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    if (factor < 0.0 || factor > 1.0)
    {
        char msg[1024];
        sprintf(msg, "Invalid factor for Blender: %f", factor);
        DataFlowException e(FilterName(), msg);
        throw e; 
    }

    // Blend input arrays using PixelBlend method (defined in image.C)
    const Pixel* inPixels = input1.GetPixels();
    const Pixel* in2Pixels = input2.GetPixels();
    for (int row=0, k=0; row<height; ++row)
        for (int col=0; col<width; ++col, ++k)
            pixels[k].PixelBlend(inPixels[k], in2Pixels[k], factor);

    GetOutput()->SetImage(width, height, pixels);
}


void Mirror::Execute(void)
{
    CheckNull(GetInput());

    const Image& input = *GetInput();

    int width = input.GetWidth();
    int height = input.GetHeight();
    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    const Pixel* inPixels = input.GetPixels();
    for (int row=0; row<height; ++row)
        for (int col=0, i=row*width, j=i+width-1; col<width; ++col,++i,--j)
            pixels[i] = inPixels[j];

    GetOutput()->SetImage(width, height, pixels);
}


void Rotate::Execute(void)
{
    CheckNull(GetInput());

    const Image& input = *GetInput();

    int width = input.GetWidth();
    int height = input.GetHeight();
    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    const Pixel* inPixels = input.GetPixels();
    for (int row=0; row<height; ++row)
    {
        int i = row*width;
        int j = height-1-row;
        for (int col=0; col<width; ++col)
        {
            pixels[j] = inPixels[i];
            i += 1;
            j += height;
        }
    }

    GetOutput()->SetImage(width, height, pixels);
}


void Subtract::Execute(void)
{
    CheckNull(GetInput());
    CheckNull(GetInput2());

    const Image& input1 = *GetInput();
    const Image& input2 = *GetInput2();

    int width = input1.GetWidth();
    int height = input1.GetHeight();

    CheckWidth(width, input2.GetWidth());
    CheckHeight(height, input2.GetHeight());

    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    const Pixel* inPixels = input1.GetPixels();
    const Pixel* in2Pixels = input2.GetPixels();
    for (int row=0, k=0; row<height; ++row)
        for (int col=0; col<width; ++col, ++k)
            pixels[k].Subtract(inPixels[k], in2Pixels[k]);

    GetOutput()->SetImage(width, height, pixels);
}


void Grayscale::Execute(void)
{
    CheckNull(GetInput());

    const Image& input = *GetInput();

    int width = input.GetWidth();
    int height = input.GetHeight();
    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    const Pixel* inPixels = input.GetPixels();
    for (int row=0, k=0; row<height; ++row)
        for (int col=0; col<width; ++col, ++k)
            pixels[k].ToGrayscale(inPixels[k]);

    GetOutput()->SetImage(width, height, pixels);
}


void Blur::Execute(void)
{
    CheckNull(GetInput());

    const Image& input = *GetInput();

    int width = input.GetWidth();
    int height = input.GetHeight();
    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));

    const Pixel* inPixels = input.GetPixels();
    for (int row=0, k=0; row<height; ++row)
        for (int col=0; col<width; ++col, ++k)
            if (row = 0 || row == height-1 || col == 0 || col == width-1)
                pixels[k] = inPixels[k];
            else
            {
                int j = k-width;
                int l = k+width;
                pixels[k].Average(inPixels[j-1], inPixels[j], inPixels[j+1],
                                  inPixels[k-1],              inPixels[k+1],
                                  inPixels[l-1], inPixels[l], inPixels[l+1]);
            }

    GetOutput()->SetImage(width, height, pixels);
}

