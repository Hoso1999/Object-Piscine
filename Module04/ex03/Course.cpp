#include "Course.hpp"
#include "Person.hpp"
#include "Professor.hpp"
#include "INotify.hpp"
#include "Student.hpp"

void Course::assign(Professor* p_professor)
{

    std::cout << "Course get Professor\n";
    auto _assignNotify = _notifyManager.getNotify(NotifyType::AssignNotify);
    auto assignNotify = std::dynamic_pointer_cast<AssignNotify>(_assignNotify);
    if (assignNotify)
        assignNotify->notify(p_professor, this);
}

void Course::assignClass(Classroom* p_class)
{
    if (p_class)
    {
        for (auto st : _students)
        {
            if (st)
                st->attendClass(p_class);
        }
    }
}

bool Course::hasStudent(Student* p_student)
{
    auto it = std::find_if(_students.cbegin(), _students.cend(),
    [&](Student* st)
    {
        return st && p_student && st == p_student;
    });
    return it != _students.end();
}

void Course::subsribe(Student* p_student)
{
    auto _subscribeNotify = _notifyManager.getNotify(NotifyType::SubscribeNotify);
    auto subscribeNotify = std::dynamic_pointer_cast<SubscribeNotify>(_subscribeNotify);
    if (subscribeNotify)
        subscribeNotify->notify(p_student, this);
}

void Course::updateGraduate(Student* p_student)
{
    auto it = std::find_if(_students.begin(), _students.end(), 
    [&](Student* st)
    {
        return st && p_student && st == p_student;
    });
    if (it != _students.end())
    {
        auto s = *it;
        if (s)
            _students.erase(it);
    }
}