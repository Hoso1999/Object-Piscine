#include "Headmaster.hpp"
#include "IObjectList.hpp"
#include "Form.hpp"
#include "Professor.hpp"
#include "Student.hpp"

void Staff::sign(Form_ptr p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    p_form->execute();
}

std::shared_ptr<Form> Headmaster::recieveRequest(FormType p_type)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto secretary = std::dynamic_pointer_cast<Secretary>(StaffList::getList().getFirst(
    [&](std::shared_ptr<Staff> st) -> bool
    {
        return st->getType() == PersonType::SECRETARY;
    }));
    if (secretary)
    {
        std::cout << "RT: " << (secretary->getType() == PersonType::SECRETARY) << "\n";
        std::cout << "Please fill Form\n";
        return secretary->createForm(p_type);
    }
    throw std::logic_error("We dont have secretary");
    // return nullptr;
}

void Headmaster::startCourses()
{
    // std::thread professors([&](){
        StaffList::getList().apply(
        [&](std::shared_ptr<Staff> st) -> bool
        {
            if (st->getType() == PersonType::PROFESSOR)
            {
                auto pr = std::dynamic_pointer_cast<Professor>(st);
                if (pr)
                {
                    pr->doClass();
                }
            }        
            return true;
        });

    // });
    // std::thread students([&](){
        StudentList::getList().apply(
        [&](std::shared_ptr<Student> st) -> bool
        {
            if (st)
                st->goClass();
            return true;
        });

    // });
    // professors.join();
    // students.join();
}
void Headmaster::setBellSystem(std::weak_ptr<BellSystem> p_bell)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    _bellSystem = p_bell;
}

void Headmaster::ringTheBell()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
        std::cout << "head try to ring\n";
    if (!_bellSystem.expired())
    {
        auto bellSystem = _bellSystem.lock();
        if (bellSystem)
        {
            StaffList::getList().apply(
            [&](std::shared_ptr<Staff> st) -> bool
            {
                if (st->getType() == PersonType::PROFESSOR)
                {
                    auto pr = std::dynamic_pointer_cast<Professor>(st);
                    if (pr)
                        pr->setBellSystem(bellSystem);
                }        
                return true;
            });
            StudentList::getList().apply(
            [&](std::shared_ptr<Student> st) -> bool
            {
                if (st->getType() == PersonType::STUDENT)
                {
                    auto pr = std::dynamic_pointer_cast<Student>(st);
                    if (pr)
                        pr->setBellSystem(bellSystem);
                }        
                return true;
            });
            std::cout << "head ringing\n";
            bellSystem->start();
        }

    }
}

void Headmaster::receiveForm(std::shared_ptr<Form> p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    std::cout << "head recieve form\n";
    auto it = std::find(_formToValidate.begin(), _formToValidate.end(), p_form);
    if (it == _formToValidate.end())
        _formToValidate.push_back(p_form);
}

bool Headmaster::confirm(std::shared_ptr<Form> p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    bool isSigned = false;
    if (p_form->validate())
    {
        isSigned = true;
        sign(p_form);
    }
    std::remove(_formToValidate.begin(), _formToValidate.end(), p_form);
    return isSigned;
}