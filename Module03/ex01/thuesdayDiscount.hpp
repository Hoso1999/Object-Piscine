#ifndef __THUESDAYDISCOUNT_HPP__
#define __THUESDAYDISCOUNT_HPP__


#include "command.hpp"

class ThuesdayDiscountCommand : public Command
{
    public:
        ThuesdayDiscountCommand(int p_id, const char* p_date, const char* p_client, const char* const* p_articles)
            :   Command(p_id, p_date, p_client, p_articles)
        {}

        void get_total_price()
        {
            /*
            * Discount of 10 percents of every command executed on a Thuesday
            */
        }
};

#endif