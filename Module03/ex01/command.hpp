#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__


class Command
{
    protected:
        int                 id;
        const char*         date;
        const char*         client;
        const char* const * articles;
    public:
        Command(int p_id, const char* p_date, const char* p_client, const char* const * p_articles)
            :   id(p_id),
                date(p_date),
                client(p_client),
                articles(p_articles)
        {}
        virtual void get_total_price() = 0;
        virtual ~Command() {}
};



#endif