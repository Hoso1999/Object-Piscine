#include "employeeManagement.hpp"
#include "hourlyEmployee.hpp"
#include "salariedEmployee.hpp"

int main(int argc, char const *argv[])
{
    EmployeeManager manager;
    TempWorker tmpWorker(5);
    tmpWorker.addWorkHour(9);
    Apprentice apprentice(7);
    apprentice.addOffHour(3);
    apprentice.addSchoolHour(2);
    ContractEmployee contactEmployee(6);
    contactEmployee.addNonWorkHour(12);
    manager.addEmployee(&tmpWorker);
    manager.addEmployee(&apprentice);
    manager.addEmployee(&contactEmployee);
    manager.executeWorkday();
    manager.calculatePayroll();
    return 0;
}
