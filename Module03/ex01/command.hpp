#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <string>
#include <map>

class Command
{
    protected:
        int                         id;
        std::string                 date;
        std::string                 client;
        std::map<std::string, int>  articles;
    public:
        Command(int p_id, const std::string& p_date, const std::string& p_client, const std::map<std::string, int>& p_articles)
            :   id(p_id),
                date(p_date),
                client(p_client),
                articles(p_articles)
        {}
        virtual void get_total_price() = 0;
        virtual ~Command() {}
};



#endif