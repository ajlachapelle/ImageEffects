#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);



    /* ================================ */
    /* START STUDENT MODIFIABLE SECTION */
    /* ================================ */

    /* you may want one or more readers! */
    PNMreader reader("puddles.pnm");  // note: filename must be "../images/image_name.pnm"


    /*   TODO: fill in fun stuff here   */
    Shrinker s;
    s.SetInput(reader.GetOutput());

    Grayscale gr;
    gr.SetInput(s.GetOutput());

    LRCombine lr1;
    lr1.SetInput(s.GetOutput());
    lr1.SetInput2(gr.GetOutput());

    Blur bl;
    bl.SetInput(s.GetOutput());

    Rotate r1;
    r1.SetInput(s.GetOutput());
    Rotate r2;
    r2.SetInput(r1.GetOutput());

    LRCombine lr2;
    lr2.SetInput(bl.GetOutput());
    lr2.SetInput2(r2.GetOutput());

    TBCombine tb;
    tb.SetInput(lr1.GetOutput());
    tb.SetInput2(lr2.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb.GetOutput();

    /* ================================ */
    /*  END STUDENT MODIFIABLE SECTION  */
    /* ================================ */



    try
    {
        finalImage->Update();

        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("out.pnm");
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}

