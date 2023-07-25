#include "Bank.hpp"

int main()
{
	Bank bank = Bank();
    bank.setLiquidity(999);
    bank.createAccount(0, 100);
    bank.createAccount(1, 100);
    bank.addValueToAccount(0, 200);

	std::cout << "Account : " << std::endl;
	std::cout << bank[0] << std::endl;
	std::cout << bank[1] << std::endl;

	std::cout << " ----- " << std::endl;

	std::cout << "Bank : " << std::endl;
	std::cout << bank << std::endl;

	return (0);
}