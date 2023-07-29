#ifndef __ILOGGER_HPP__
#define __ILOGGER_HPP__

#include <string>
#include "IHeader.hpp"


class ILogger
{
    public:
        ILogger() {};
        virtual void write(std::string) = 0;
        virtual ~ILogger() {};
};




#endif