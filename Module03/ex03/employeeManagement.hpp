#ifndef __EMPLOYEEMANAGEMENT_HPP__
#define __EMPLOYEEMANAGEMENT_HPP__

#include "employee.hpp"
#include <set>

class EmployeeManager
{
    private:
        std::set<Employee*> employees;
    public:
        EmployeeManager(/* args */) {}
        void addEmployee(Employee*) {}
        void removeEmployee(Employee*) {}
        void executeWorkday() {}
        void calculatePayroll() {}
};




#endif