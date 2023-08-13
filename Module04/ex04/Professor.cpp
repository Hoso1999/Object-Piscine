#include "Person.hpp"
#include "Professor.hpp"
#include "Room.hpp"
#include "INotify.hpp"
#include "IObjectList.hpp"
#include "Form.hpp"
#include "Headmaster.hpp"
#include "Form.hpp"
#include "Student.hpp"
#include "NotifyManager.hpp"
#include "RequestToHead.hpp"

void Professor::assignCourse(Course* p_course)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    /*
        * I think dynamic_casts is worst solution but it works
        * maybe inherit all Person types from concrete enable_shared_from_this?
    */
    auto _assignNotify = _notifyManager.getNotify(NotifyType::AssignNotify);
    auto assignNotify = std::dynamic_pointer_cast<AssignNotify>(_assignNotify);
    if (assignNotify)
        assignNotify->notify(this, p_course);
}

void Professor::sendRequest(FormType p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto head = std::dynamic_pointer_cast<Headmaster>(StaffList::getList().getFirst(
    [&](std::shared_ptr<Staff> st) -> bool
    {
        return st->getType() == PersonType::HEADMASTER;
    }));
    if (head)
    {
        switch (p_form)
        {
            case FormType::NeedCourseCreation:
            {
                auto _notify = _notifyManager.getNotify(NotifyType::NoCourseNotify);
                std::cout << "try create course\n";
                auto notify = std::dynamic_pointer_cast<NoCourseNotify>(_notify);
                if (notify)
                    notify->notify(this, head.get());
           
                break;
            }
            case FormType::NeedMoreClassRoom:
            {
                std::cout << "No enough class create one\n";
                auto _notify = _notifyManager.getNotify(NotifyType::NoClassNotify);
                auto notify = std::dynamic_pointer_cast<NoClassNotify>(_notify);
                if (notify)
                    notify->notify(this, head.get());
                break;
            }
            case FormType::CourseFinished:
            {
                std::cout << "Have student to graduate\n";
                auto _notify = _notifyManager.getNotify(NotifyType::GraduateNotify);
                auto notify = std::dynamic_pointer_cast<GraduateNotify>(_notify);
                if (notify)
                    notify->notify(this, head.get());
               
                break;
            }
        
        default:
            std::logic_error("Action not implemented");
            break;
        }
        // request with RequestToHead
    }

}

void Professor::doClass()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (!hasCourse())
    {
        std::cout << "I have no course\n";
        sendRequest(FormType::NeedCourseCreation);
    }
    auto course = _currentCourse;
    if (course)
    {
        std::cout << "Professor search empty room\n";
        auto emptyRoom = RoomList::getList().getFirst(
        [&](std::shared_ptr<Room> p_room) -> bool
        {
            return p_room->getType() == RoomType::CLASSROOM && p_room->canEnter(this);
        });
        if (emptyRoom)
        {
            enterRoom(emptyRoom.get());
            course->assignClass(dynamic_cast<Classroom*>(emptyRoom.get()));
            std::cout << "Professor in class\n";
        }
        else
        {
            std::cout << "No empty room try to create\n";
            sendRequest(FormType::NeedMoreClassRoom);
            auto emptyRoom = RoomList::getList().getFirst(
            [&](std::shared_ptr<Room> p_room) -> bool
            {
                return p_room->getType() == RoomType::CLASSROOM && p_room->canEnter(this);
            });
            if (emptyRoom)
            {
                enterRoom(emptyRoom.get());
                course->assignClass(dynamic_cast<Classroom*>(emptyRoom.get()));
            }
        }
        course->apply([&](Student* student) -> bool
        {
            if (student)
            {
                student->learn();
                if (student->numberOfClasses() == course->numberClassToGraduate())
                {
                    std::cout << "Need student to graduate\n";
                    sendRequest(FormType::CourseFinished);
                    _requests.push(student);
                }
            }
            return true;
        });
        std::cout << "Professor finished Class" << std::endl;
        exitRoom();
        course->apply(
        [&](Student* st) -> bool
        {
            if (st)
                st->exitClass();
            return true;
        });
    }
}

void Professor::update(Event p_event)
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
                    auto rest = RoomList::getList().getFirst(
                    [&](std::shared_ptr<Room> r) -> bool
                    {
                        return r->getType() == RoomType::STAFFRESTROOM;
                    });
                    if (rest)
                    {
                        std::cout << "Professor " << _name << " go to rest Room " << rest->getID() << "\n";
                        enterRoom(dynamic_cast<Room*>(rest.get()));
                    }
                }
                else
                {
                    std::cout << "Professor " << _name << " return to class\n";
                    enterRoom(_lastRoom);
                }
            }
        }
    }
}

void Professor::setBellSystem(std::weak_ptr<BellSystem> p_bell)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (!p_bell.expired())
    {
        auto bell = p_bell.lock();
        if (bell)
        {
            bell->addListener( dynamic_cast<Listener*> (this));
            _bellSystem = bell;
        }
    }
}

void Professor::fillForm(std::shared_ptr<Form> p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    switch (p_form->getType())
    {
        case FormType::NeedCourseCreation:
        {
            std::cout << "start fill form\n";
            auto form = std::dynamic_pointer_cast<NeedCourseCreationForm>(p_form);
            form->setSubject("hello");
            form->assign(this);
            break;
        }
        case FormType::CourseFinished:
        {
            // std::cout << "start fill course\n";
            auto form = std::dynamic_pointer_cast<CourseFinishedForm>(p_form);
            form->setResponsable(this);
            if (!_requests.empty())
            {
                auto student = _requests.front();
                if (student)
                {
                    form->setStudent(student);
                    form->finish(true);
                    _requests.pop();
                }
            }
            break;
        }
        default:
            throw std::logic_error("Not implemented");
            break;
    }
}
void Professor::updateSigned(bool p_signed)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (p_signed)
    {

    }
}

void Professor::closeCourse()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    _currentCourse = nullptr;
}