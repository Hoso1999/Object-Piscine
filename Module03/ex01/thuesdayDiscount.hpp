#ifndef __THUESDAYDISCOUNT_HPP__
#define __THUESDAYDISCOUNT_HPP__


#include "command.hpp"
#include <iostream>

class ThuesdayDiscountCommand : public Command
{
    public:
        ThuesdayDiscountCommand(int p_id, const std::string& p_date, const std::string& p_client, const std::map<std::string, int>& p_articles)
            :   Command(p_id, p_date, p_client, p_articles)
        {}

        void get_total_price()
        {
                std::cout << "Discount of 10 percents of every command executed on a Thuesday" << std::endl;
        }
};

#endif