#include "Course.hpp"
#include "Person.hpp"
#include "Professor.hpp"
#include "INotify.hpp"
#include "Student.hpp"
#include "Room.hpp"
#include <mutex>


Course::Course(std::string p_name)
    :	_name(p_name),
        _numberOfClassToGraduate(2),
        _maximumNumberOfStudent(5),
        _responsable(nullptr),
        _notifyManager(NotifyManager::getNotifyManager())
{}

void Course::assign(Professor* p_professor)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    std::cout << "Course [ " << _name << " ] - Get Professor " << "[ " << p_professor->getName() << " ]" << std::endl;
    auto assignNotify = _notifyManager.getNotify<AssignNotify>(NotifyType::AssignNotify);
    if (assignNotify)
        assignNotify->notify(p_professor, this);
}

void Course::assignClass(Classroom* p_class)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    
    if (p_class)
    {
        std::cout << "Course [ " << _name << " ] - Go to Classroom [ " << p_class->getID() << " ]" << std::endl;
        for (auto st : _students)
        {
            if (st)
                st->attendClass(p_class);
        }
    }
}

bool Course::hasStudent(Student* p_student)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto it = std::find_if(_students.cbegin(), _students.cend(),
    [&](Student* st)
    {
        return st && p_student && st == p_student;
    });
    return it != _students.end();
}

void Course::subsribe(Student* p_student)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto subscribeNotify = _notifyManager.getNotify<SubscribeNotify>(NotifyType::SubscribeNotify);
    if (subscribeNotify)
        subscribeNotify->notify(p_student, this);
}

void Course::updateGraduate(Student* p_student)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto it = std::find_if(_students.begin(), _students.end(), 
    [&](Student* st)
    {
        return p_student && st && st == p_student;
    });
    if (it != _students.end())
    {
        auto s = *it;
        if (s)
            _students.erase(it);
    }
}