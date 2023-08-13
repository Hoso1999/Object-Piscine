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
#include "Wrappers.hpp"

void Professor::assignCourse(Course* p_course)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    /*
        * I think dynamic_casts is worst solution but it works
        * maybe inherit all Person types from concrete enable_shared_from_this?
    */
    auto assignNotify = _notifyManager.getNotify<AssignNotify>(NotifyType::AssignNotify);
    if (assignNotify)
        assignNotify->notify(this, p_course);
}

void Professor::sendRequest(FormType p_form)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto head = std::dynamic_pointer_cast<Headmaster>(Lambda<StaffList>::getFirst(
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
                std::cout << "Professor [ " << _name << " ] - Fills form for Course Creation" << std::endl;
                auto notify = _notifyManager.getNotify<NoCourseNotify>(NotifyType::NoCourseNotify);
                if (notify)
                    notify->notify(this, head.get());
           
                break;
            }
            case FormType::NeedMoreClassRoom:
            {
                std::cout << "Professor [ " << _name << " ] - Fills form for Classroom Creation" << std::endl;
                auto notify = _notifyManager.getNotify<NoClassNotify>(NotifyType::NoClassNotify);
                if (notify)
                    notify->notify(this, head.get());
                break;
            }
            case FormType::CourseFinished:
            {
                std::cout << "Professor [ " << _name << " ] - Fills form for Student Graduation" << std::endl;
                auto notify = _notifyManager.getNotify<GraduateNotify>(NotifyType::GraduateNotify);
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

void Professor::searchEmptyRoom(Classroom* p_currentClass, Course* p_course)
{
    std::cout << "Professor [ " << _name << " ] - Search empty room" << std::endl;
    auto emptyRoom = dynamic_cast<Classroom*>(Lambda<RoomList>::getFirst(
    [&](std::shared_ptr<Room> p_room) -> bool
    {
        return p_room->getType() == RoomType::CLASSROOM && p_room->canEnter(this);
    }).get());
    if (emptyRoom)
    {
        p_currentClass = emptyRoom;
        enterRoom(emptyRoom);
        emptyRoom->assignCourse(p_course);
        p_course->assignClass(emptyRoom);
        std::cout << "Professor [ " << _name << " ] - Go to classroom" << std::endl;

    }
    else
    {
        std::cout << "Professor [ " << _name << " ] - No empty room try to create" << std::endl;
        sendRequest(FormType::NeedMoreClassRoom);
        searchEmptyRoom(p_currentClass, p_course);
    }
}

void Professor::doClass()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (!hasCourse())
    {
        std::cout << "Professor [ " << _name << " ] - I have no course" << std::endl;
        sendRequest(FormType::NeedCourseCreation);
    }
    Classroom* currentClass = nullptr;
    auto course = _currentCourse;
    if (course)
    {
        searchEmptyRoom(currentClass, course);
        course->apply([&](Student* student) -> bool
        {
            if (student)
                student->learn();
            return true;
        });
        std::cout << "Professor [ " << _name << " ] - Finished Class [ " << course->getName() << " ]" << std::endl;
        if (currentClass)
            currentClass->removeCourse();
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
        if (_bellSystem)
        {
            if (_bellSystem->isFreeTime())
            {
                _lastRoom = _currentRoom;
                auto rest = Lambda<RoomList>::getFirst(
                [&](std::shared_ptr<Room> r) -> bool
                {
                    return r->getType() == RoomType::STAFFRESTROOM;
                });
                if (rest)
                {
                    std::cout << "Professor [ " << _name << " ] - Go to rest Room " << rest->getID() << std::endl;
                    enterRoom(rest.get());
                }
            }
            else if (_lastRoom)
            {
                std::cout << "Professor [ " << _name << " ] - return to Classroom [ " << _lastRoom->getID() << " ]" << std::endl;
                enterRoom(_lastRoom);
            }
        }
    }
}

void Professor::setBellSystem(BellSystem* p_bell)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (p_bell)
    {
        p_bell->addListener(this);
        _bellSystem = p_bell;
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
            std::cout << "Professor [ " << _name << " ] - Start fill [ Form ] for Course Creation" << std::endl;
            auto form = std::dynamic_pointer_cast<NeedCourseCreationForm>(p_form);
            form->setSubject(_name + "_subject");
            form->assign(this);
            break;
        }
        case FormType::NeedMoreClassRoom:
        {
            std::cout << "Professor [ " << _name << " ] - Start fill [ Form ] for Classroom Creation" << std::endl;
            auto form = std::dynamic_pointer_cast<NeedMoreClassRoomForm>(p_form);
            form->creation(_currentCourse);
            break;
        }
        case FormType::CourseFinished:
        {
            std::cout << "Professor [ " << _name << " ] - Start fill [ Form ] for Student Graduation" << std::endl;
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
            throw std::runtime_error("Not implemented");
            break;
    }
}
void Professor::updateSigned(bool p_signed, FormType type)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    // if (p_signed && type != FormType::CourseFinished)
    //     doClass();
}

void Professor::closeCourse()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    _currentCourse = nullptr;
}