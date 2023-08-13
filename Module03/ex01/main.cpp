#include "packageReductionDiscount.hpp"
#include "thuesdayDiscount.hpp"


int main(int argc, char const *argv[])
{
    int id = 0;
    const char* date = "Thuesday";
    const char* client = "client";
    const char* const* articles = (char*[]){"hello", "world"};
    PackageReductionDiscountCommand reduction(id, date, client, articles);
    ThuesdayDiscountCommand thuesdayCommand(id, date, client, articles);
    reduction.get_total_price();
    thuesdayCommand.get_total_price();
    return 0;
}
