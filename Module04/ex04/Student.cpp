#include "IObjectList.hpp"
#include "Course.hpp"
#include "Room.hpp"
#include "INotify.hpp"
#include "Student.hpp"
#include "RequestToHead.hpp"
#include "Form.hpp"

Student::Student(std::string p_name)
	:	Person(p_name)
{}

void Student::attendClass(Classroom* p_class)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    enterRoom(dynamic_cast<Room*> (p_class));
}

void Student::graduate(Course* p_course)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto it = std::find_if(_subscribedCourse.cbegin(), _subscribedCourse.cend(), 
    [&](Course* c)
    {
        return (c && p_course && c == p_course);
    });
    if (it != _subscribedCourse.cend())
        _subscribedCourse.erase(it);
}

void Student::goClass()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto head = std::dynamic_pointer_cast<Headmaster>(StaffList::getList().getFirst(
    [&](std::shared_ptr<Staff> st) -> bool
    {
        return st->getType() == PersonType::HEADMASTER;
    }));
    if (!_subscribedCourse.size())
    {
        std::cout << "No anough courses create please\n";
        auto _joinNotify = _notifyManager.getNotify(NotifyType::JoinNotify);
        auto joinNotify = std::dynamic_pointer_cast<JoinCourseNotify>(_joinNotify);
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
            std::cout << "try subscript to course\n";
            auto firstCourse = CourseList::getList().getFirst(
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

void Student::setBellSystem(std::weak_ptr<BellSystem> p_bell)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (!p_bell.expired())
    {
        auto bell = p_bell.lock();
        if (bell)
        {
            _bellSystem = bell;
            bell->addListener( dynamic_cast<Listener*> (this));
        }
    }
}

void Student::update(Event p_event)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (p_event == Event::RingBell)
    {
        if (!_bellSystem.expired())
        {
            auto bellSystem = _bellSystem.lock();
            if (bellSystem)
            {
                if (bellSystem->isFreeTime())
                {
                    _lastRoom = _currentRoom;
                    auto courtyard = RoomList::getList().getFirst(
                    [&](std::shared_ptr<Room> r) -> bool
                    {
                        return r->getType() == RoomType::COURTYARD;
                    });
                    if (courtyard)
                    {
                        std::cout << "Student " << _name << " go to courtyard " << courtyard->getID() << "\n";
                        enterRoom(dynamic_cast<Room*>(courtyard.get()));
                    }
                }
                else
                {
                    std::cout << "Student " << _name << " return to class\n";
                    enterRoom(_lastRoom);
                }
            }

        }
    }
}

void Student::subcribe(Course* p_course)
{

    auto _subscribeNotify = _notifyManager.getNotify(NotifyType::SubscribeNotify);
    auto subscribeNotify = std::dynamic_pointer_cast<SubscribeNotify>(_subscribeNotify);
    if (subscribeNotify)
        subscribeNotify->notify(this, p_course);
}
