#include "IObjectList.hpp"
#include "Course.hpp"
#include "Room.hpp"
#include "INotify.hpp"
#include "Student.hpp"
#include "RequestToHead.hpp"
#include "Form.hpp"
#include "Wrappers.hpp"

Student::Student(std::string p_name)
	:	Person(p_name),
        _bellSystem(nullptr),
        _lastRoom(nullptr),
        _numberOfClasses(0)
{}

void Student::attendClass(Classroom* p_class)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    enterRoom(p_class);
}

void Student::graduate(Course* p_course)
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto it = std::find_if(_subscribedCourse.cbegin(), _subscribedCourse.cend(), 
    [&](Course* c)
    {
        return c && p_course && c == p_course;
    });
    if (it != _subscribedCourse.cend())
        _subscribedCourse.erase(it);
}

void Student::goClass()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto head = std::dynamic_pointer_cast<Headmaster>(Lambda<StaffList>::getFirst(
    [&](std::shared_ptr<Staff> st) -> bool
    {
        return st->getType() == PersonType::HEADMASTER;
    }));
    if (!_subscribedCourse.size())
    {
        std::cout << "Student [ " << _name << " ] - i dont have any course. Please create" << std::endl;
        auto joinNotify = _notifyManager.getNotify<JoinCourseNotify>(NotifyType::JoinNotify);
        if (joinNotify && head)
            joinNotify->notify(this, head.get());
    }
}

void Student::fillForm(std::shared_ptr<Form> p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    switch (p_form->getType())
    {
        case FormType::SubscriptionToCourse:
        {
            std::cout << "Student [ " << _name << " ] - Fill the form" << std::endl;
            auto firstCourse = Lambda<CourseList>::getFirst(
            [&](std::shared_ptr<Course> c) -> bool
            {
                return !c->isFull();
            });
            auto form = std::dynamic_pointer_cast<SubscriptionToCourseForm>(p_form);
            form->from(this);
            if (firstCourse)
                form->subscript(firstCourse.get());
            break;
        }
        
        default:
        {
            throw std::logic_error("Not implemented");
            break;
        }
    }
}

void Student::setBellSystem(BellSystem* p_bell)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (p_bell)
    {
        _bellSystem = p_bell;
        p_bell->addListener( dynamic_cast<Listener*> (this));
    }
}

void Student::update(Event p_event)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (p_event == Event::RingBell)
    {
        if (_bellSystem)
        {
            if (_bellSystem->isFreeTime())
            {
                _lastRoom = _currentRoom;
                auto courtyard = Lambda<RoomList>::getFirst(
                [&](std::shared_ptr<Room> r) -> bool
                {
                    return r->getType() == RoomType::COURTYARD;
                });
                if (courtyard)
                {
                    std::cout << "Student [" << _name << " ] go to courtyard [ " << courtyard->getID() << " ]" << std::endl;
                    enterRoom(courtyard.get());
                }
            }
            else if (_lastRoom)
            {
                std::cout << "Student [ " << _name << " ] return to classroom [ " << _lastRoom->getID() << " ]" << std::endl;
                enterRoom(_lastRoom);
            }
        }
    }
}

void Student::subcribe(Course* p_course)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto subscribeNotify = _notifyManager.getNotify<SubscribeNotify>(NotifyType::SubscribeNotify);
    if (subscribeNotify)
        subscribeNotify->notify( this, p_course);
}
