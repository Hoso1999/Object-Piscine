#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "Bank.hpp"

class Bank::Account
{
    int id;
    int value;

    public:
        Account()
            :   id(-1),
                value(0)
        {}

        Account(int p_id, int p_value)
        :   id(p_id),
            value(p_value)
        {}

        int getId() const
        {
            return id;
        }

        int getValue() const
        {
            return value;
        }
        friend class ::Bank;
};

std::ostream& operator<<( std::ostream& p_os, const Bank::Account& p_account )
{
    p_os << "[" << p_account.getId() << "] - [" << p_account.getValue() << "]";
    return (p_os);
}

Bank::Bank()
    :   accountImpl(new Account()),  
        liquidity(0)
{}

Bank::Bank(int p_liquidity)
    :   accountImpl(new Account()),
        liquidity(p_liquidity)
{}

Bank::~Bank()
{
    for (iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it)
        if (it->second)
            delete it->second;
    delete accountImpl;
}

void Bank::createAccount(int p_id, int p_value)
{
    iterator it = clientAccounts.find(p_id);
    if (it != clientAccounts.end())
        throw std::logic_error("Bank: Accounts cannot have same ID");
    clientAccounts[p_id] = new Account(p_id, p_value);
}

void Bank::modifyAccount(int p_id, int p_value)
{
    iterator it = clientAccounts.find(p_id);
    if (it == clientAccounts.end())
        throw std::logic_error("Bank: no such account");
    it->second->value = p_value;
}

void    Bank::getLoan(int p_id, int amount)
{
    iterator it = clientAccounts.find(p_id);
    if (it == clientAccounts.end())
        throw std::logic_error("Bank: no such account");
    if (liquidity < amount)
        throw std::logic_error("Bank: no enough funds");
    liquidity -= amount;
    it->second->value += amount;
}


void    Bank::addValueToAccount(int p_id, int p_value)
{
    iterator it = clientAccounts.find(p_id);
    if (it == clientAccounts.end())
        throw std::logic_error("Bank: no such account");
    int amount = p_value * 0.05;
    liquidity += amount;
    it->second->value += p_value - amount;
}

void    Bank::subValueToAccount(int p_id, int p_value)
{
    iterator it = clientAccounts.find(p_id);
    if (it == clientAccounts.end())
        throw std::logic_error("Bank: no such account");
    it->second->value -= p_value;
}

std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.getLiquidity() << std::endl;
    const Bank::container_type& accounts = p_bank.getClientAccounts();
    for (Bank::const_iterator it = accounts.begin(); it != accounts.end(); ++it)
        p_os << *it->second << std::endl;
    return (p_os);
}

#endif