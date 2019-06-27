// Alex LaChapelle
// CS 330 Project 3E

#include <string.h>
#include <image.h>
#include <source.h>
#include <logging.h>

Source::Source(void)
{
}

void Source::Update(void)
{
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

Image* Source::GetOutput(void)
{
    img.SetSource(this);
    return &img;
}

