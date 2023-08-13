#ifndef __INOTIFY_HPP__
#define __INOTIFY_HPP__

#include <algorithm>
#include <memory>
// #include "Person.hpp"
// #include "Student.hpp"
// #include "Staff.hpp"
// #include "Professor.hpp"
// #include "Course.hpp"
// #include "Room.hpp"

class Student;
class Course;
class Room;
class Classroom;
class Professor;
class Person;
class Headmaster;

class RoomEnterNotify;
class RoomExitNotify;

enum class NotifyType
{
    SubscribeNotify,
    UnsubscribeNotify,
    AssignNotify,
    RoomEnterNotify,
    RoomExitNotify,
    NoCourseNotify,
    NoClassNotify,
    GraduateNotify,
    JoinNotify
};


/*
 * there can be better solution but it works
 * can be soulution that avoids dynamic_casts?
*/

class INotifyBase
{
    protected:
        NotifyType _type;

        INotifyBase(NotifyType p_type)
            :   _type(p_type)
        {}
    public:
        NotifyType getType() const
        {
            return _type;
        }
        virtual ~INotifyBase() {}
};

template<NotifyType type, typename T1, typename T2>
class INotify : public INotifyBase
{
    protected:
        using sender_ptr = T1*;
        using recieve_ptr = T2*;
    public:
        INotify()
            :   INotifyBase(type)
        {}
        virtual void notify(sender_ptr, recieve_ptr) = 0;
};

class SubscribeNotify : public INotify<NotifyType::SubscribeNotify, Student, Course>
{
    protected:
        using sender_ptr = Student*;
        using recieve_ptr = Course*;
    public:
        SubscribeNotify()
            :   INotify<NotifyType::SubscribeNotify, Student, Course>()
        {}
        void notify(sender_ptr p_sender, recieve_ptr p_recieve) override;
};

class UnsubscribeNotify : public INotify<NotifyType::UnsubscribeNotify, Student, Course>
{
    protected:
        using sender_ptr = Student*;
        using recieve_ptr = Course*;
    public:
        UnsubscribeNotify()
            :   INotify<NotifyType::UnsubscribeNotify, Student, Course>()
        {}
        void notify(sender_ptr p_sender, recieve_ptr p_recieve) override;
};

class AssignNotify : public INotify<NotifyType::AssignNotify, Professor, Course>
{
    protected:
        using sender_ptr = Professor*;
        using recieve_ptr = Course*;
    public:
        AssignNotify()
            :   INotify<NotifyType::AssignNotify, Professor, Course>()
        {}
        void notify(sender_ptr p_sender, recieve_ptr p_recieve) override;
};

class RoomEnterNotify : public INotify<NotifyType::RoomEnterNotify, Room, Person>
{
    protected:
        using sender_ptr = Room*;
        using recieve_ptr = Person*;
    public:
        RoomEnterNotify()
            :   INotify<NotifyType::RoomEnterNotify, Room, Person>()
        {}
        void notify(sender_ptr p_sender, recieve_ptr p_recieve) override;
};

class RoomExitNotify : public INotify<NotifyType::RoomExitNotify, Room, Person>
{
    protected:
        using sender_ptr = Room*;
        using recieve_ptr = Person*;
    public:
        RoomExitNotify()
            :   INotify<NotifyType::RoomExitNotify, Room, Person>()
        {}
        void notify(sender_ptr p_sender, recieve_ptr p_recieve) override;
};


#endif