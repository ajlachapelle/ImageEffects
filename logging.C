
#include <logging.h>

DataFlowException::DataFlowException(const char* type, const char* error)
{
    sprintf(msg, "Throwing exception: (%s): %s", type, error);
    Logger::LogEvent(msg);
}


FILE* Logger::logger = fopen("logger.out", "w");

void Logger::LogEvent(const char* event)
{
//    if (!logger) throw exception

    fprintf(logger, "%s\n", event);
    fflush(logger);
}

void Logger::LogEvent(const char* location, const char* event)
{
//    if (!logger) throw exception

    fprintf(logger, "%s: %s\n", location, event);
    fflush(logger);
}

void Logger::Finalize()
{
    fclose(logger);
}

