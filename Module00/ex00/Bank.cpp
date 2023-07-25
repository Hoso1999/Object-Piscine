#include "Bank.hpp"

void Bank::setLiquidity(int p_liquidity)
{
    this->liquidity = p_liquidity;
}

int Bank::getLiquidity() const
{
   return liquidity;
}

const Bank::Account& Bank::operator[](int p_id) const
{
    iterator it = clientAccounts.find(p_id);
    if (it == clientAccounts.end())
        throw std::logic_error("Bank: no such account");
    return *clientAccounts[p_id];
}

const Bank::container_type&           Bank::getClientAccounts() const
{
    return clientAccounts;
}

Bank::container_type&                 Bank::getClientAccounts()
{
    return clientAccounts;
}

void Bank::deleteAccount(int p_id)
{
    iterator it = clientAccounts.find(p_id);
    if (it == clientAccounts.end())
        throw std::logic_error("Bank: no such account");
    clientAccounts.erase(p_id);
}
