#include "packageReductionDiscount.hpp"
#include "thuesdayDiscount.hpp"


int main(int argc, char const *argv[])
{
    int id = 0;
    std::string date = "Thuesday";
    std::string client = "client";
    std::map<std::string, int> articles;
    articles["hello"] = 8;
    PackageReductionDiscountCommand reduction(id, date, client, articles);
    ThuesdayDiscountCommand thuesdayCommand(id, date, client, articles);
    reduction.get_total_price();
    thuesdayCommand.get_total_price();
    return 0;
}
