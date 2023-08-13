#ifndef __EMPLOYEE_HPP__
#define __EMPLOYEE_HPP__

class Employee
{
    int hourlyValue;
    public:
        Employee( int p_hourly_value)
            :   hourlyValue(p_hourly_value)
        {}
        virtual int executeWorkday() = 0;
        virtual ~Employee() {}
};

class Apprentice : public Employee
{
    int offHour;
    int schoolHour;
    public:
        Apprentice(int p_hourly_value)
            :   Employee(p_hourly_value),
                offHour(0),
                schoolHour(0)
        {}
        void addOffHour(int) {}
        void addSchoolHour(int) {}
        int executeWorkday()
        {
            /*
            * Implemenation for Apprentice
            */
            return 9;
        }
};


#endif