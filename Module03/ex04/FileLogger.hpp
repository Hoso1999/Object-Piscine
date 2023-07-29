#ifndef __FILELOGGER_HPP__
#define __FILELOGGER_HPP__

#include "ILogger.hpp"

#include <fstream>

class FileLogger : public ILogger
{
    std::string filename;
    IHeader*    header;
    public:
        FileLogger(std::string p_filename, IHeader* p_header = 0)
            :   ILogger(),
                header(p_header),
                filename(p_filename)
        {}
        void write(std::string str)
        {
            std::fstream fs(filename);
            if (header)
                fs << header->to_string();
            fs << str;
        }
};

#endif