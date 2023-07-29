#include "ILogger.hpp"
#include "OutLogger.hpp"
#include "FileLogger.hpp"

int main(int argc, char const *argv[])
{
    IHeader* header = new StringHeader("hello: ");
    ILogger* logger = new OutLogger(header);
    logger->write("hi");
    return 0;
}
