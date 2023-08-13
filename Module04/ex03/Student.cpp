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
    enterRoom(dynamic_cast<Room*> (p_class));
}

void Student::graduate(Course* p_course)
{
    auto it = std::find_if(_subscribedCourse.cbegin(), _subscribedCourse.cend(), 
    [&](Course* c)
    {
        return (c == p_course);
    });
    if (it != _subscribedCourse.cend())
        _subscribedCourse.erase(it);
}

void Student::goClass()
{
    auto head = std::dynamic_pointer_cast<Headmaster>(StaffList::getList().getFirst(
    [&](std::shared_ptr<Staff> st) -> bool
    {
        return st->getType() == PersonType::HEADMASTER;
    }));
    if (!_subscribedCourse.size())
    {
        auto _joinNotify = _notifyManager.getNotify(NotifyType::JoinNotify);
        auto joinNotify = std::dynamic_pointer_cast<JoinCourseNotify>(_joinNotify);
        if (joinNotify && head)
            joinNotify->notify(this, head.get());
    }
}

void Student::fillForm(std::shared_ptr<Form> p_form)
{
    switch (p_form->getType())
    {
        case FormType::SubscriptionToCourse:
        {
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

void Student::subcribe(Course* p_course)
{

    auto _subscribeNotify = _notifyManager.getNotify(NotifyType::SubscribeNotify);
    auto subscribeNotify = std::dynamic_pointer_cast<SubscribeNotify>(_subscribeNotify);
    if (subscribeNotify)
        subscribeNotify->notify(this, p_course);
}
