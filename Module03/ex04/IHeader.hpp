#ifndef __IHEADER_HPP__
#define __IHEADER_HPP__

#include <string>

class IHeader
{
    public:
        IHeader() {}
        virtual ~IHeader() {}
        virtual const std::string& to_string() = 0;
};

class StringHeader : public IHeader
{
    std::string msg;

    public:
        StringHeader(const std::string& str)
            :   IHeader(),
                msg(str)
        {}
        const std::string& to_string()
        {
            return msg;
        }
};

class DataHeader : public IHeader
{
    std::string date;
    public:
        DataHeader(const std::string& str)
            :   IHeader(),
                date(str)
        {}
        const std::string& to_string()
        {
            /* 
            * convert date to string
            */
            return date;
        }
};

class NonHeader : public IHeader
{
    public:
        NonHeader()
            :   IHeader()
        {}
        const std::string& to_string()
        {
            /*
            * no header
            */
            return "";
        }
};

#endif