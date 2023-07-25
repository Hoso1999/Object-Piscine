#ifndef __BANK_HPP__
#define __BANK_HPP__


#include <iostream>
#include <vector>
#include <map>

class Bank
{
    public:
        class Account;
        typedef std::map<int, Account*> container_type;
        typedef std::map<int, Account*>::iterator iterator;
        typedef std::map<int, Account*>::const_iterator const_iterator;

    private:
        /* 
        *  Implemenation for Account
        */
        Account* accountImpl;
        int liquidity;
        mutable container_type clientAccounts;
    public:
        Bank();
        Bank(int p_liquidity);
        ~Bank();

        void                            setLiquidity(int p_liquidity);

        int                             getLiquidity() const;

        const Account&                  operator[](int id) const;
        
        void                            createAccount(int p_id, int p_value);
        void                            modifyAccount(int p_id, int p_value);
        void                            deleteAccount(int p_id);
        void                            addValueToAccount(int p_id, int p_value);
        void                            subValueToAccount(int p_id, int p_value);
        void                            getLoan(int p_id, int amount);
        const container_type&           getClientAccounts() const;
        container_type&                 getClientAccounts();
};
std::ostream& operator << (std::ostream& p_os, const Bank& p_bank);
std::ostream& operator<<( std::ostream& p_os, const Bank::Account& p_account );



#endif