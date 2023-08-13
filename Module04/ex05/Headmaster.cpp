#include "Headmaster.hpp"
#include "IObjectList.hpp"
#include "Form.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include <future>
#include "Wrappers.hpp"

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
    auto secretary = std::dynamic_pointer_cast<Secretary>(Lambda<StaffList>::getFirst(
    [&](std::shared_ptr<Staff> st) -> bool
    {
        return st->getType() == PersonType::SECRETARY;
    }));
    if (secretary)
    {
        std::cout << "Headmater [ " << _name << " ] - get form from secretary" << std::endl;
        return secretary->createForm(p_type);
    }
    throw std::logic_error("We dont have secretary");
}

void Headmaster::startCourses()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto a1 = std::async([&](){

        Lambda<ProfessorList>::apply(
        [&](std::shared_ptr<Professor> pr) -> bool
        {
            auto a = std::async([&](){
                if (pr)
                    pr->doClass();
            });
            return true;
        });
    });
    auto a2 = std::async([&](){

        Lambda<StudentList>::apply(
        [&](std::shared_ptr<Student> st) -> bool
        {
            auto a3 = std::async([&](){
            if (st)
                st->goClass();
            });
            return true;
        });
    });


}
void Headmaster::setBellSystem(BellSystem* p_bell)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    _bellSystem = p_bell;
}

void Headmaster::ringTheBell()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    std::cout << "Headmaster [ " << _name << " ] - Ring the bell" << std::endl;
    if (_bellSystem)
    {
        std::cout << "Headmaster [ " << _name << " ] - Ringing" << std::endl;
        _bellSystem->start();
    }

}

void Headmaster::receiveForm(std::shared_ptr<Form> p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    std::cout << "Headmaster [ " << _name << " ] - Recieve form type [ " << (int)p_form->getType() << " ]" << std::endl;
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
        std::remove(_formToValidate.begin(), _formToValidate.end(), p_form);
    }
    return isSigned;
}