#ifndef __PACKAGEREDUCTIONDISCOUNT_HPP__
#define __PACKAGEREDUCTIONDISCOUNT_HPP__

#include "command.hpp"

class PackageReductionDiscountCommand : public Command
{
    public:
        PackageReductionDiscountCommand(int p_id, const char* p_date, const char* p_client, const char* const * p_articles)
            :   Command(p_id, p_date, p_client, p_articles)
        {}

        void get_total_price()
        {
            /*
            * Discount of 10 euro if the total command value exceed 150 euros
            */
        }
};



#endif