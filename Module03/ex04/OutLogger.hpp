#ifndef __OUTLOGGER_HPP__
#define __OUTLOGGER_HPP__

#include "ILogger.hpp"
#include <iostream>

class OutLogger : public ILogger
{
    IHeader* header;
    public:
        OutLogger(IHeader* p_header = 0)
            :   ILogger(),
                header(p_header)
        {}
        void write(std::string str)
        {
            if (header)
                std::cout << header->to_string();
            std::cout << str;
        }
};

#endif


