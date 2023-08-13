#ifndef __EMPLOYEEMANAGEMENT_HPP__
#define __EMPLOYEEMANAGEMENT_HPP__

#include "employee.hpp"

class EmployeeManager
{
    private:
        Employee** employees;
    public:
        EmployeeManager(/* args */) {}
        void addEmployee(Employee*)
        {
            /*
            * Implementation for add Employee 
            */
        }

        void removeEmployee(Employee*)
        {
            /*
            * Implementation for remove Employee
            */
        }

        void executeWorkday()
        {
            /*
            * This method must execute a single day of work for each of the registered worker.
            * One day equal 7 hours of work
            */   
        }

        void calculatePayroll()
        {
            /*
            * This method must output in the console the amount of money to give to each of
            * the subscribed workers, over the last complete month.
            */
        }
};




#endif