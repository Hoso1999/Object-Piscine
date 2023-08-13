#ifndef __ILIST_HPP__
#define __ILIST_HPP__

#include <list>
#include <shared_mutex>
#include <memory>
#include <functional>
#include <algorithm>
#include <type_traits>

class Student;
class Professor;
class Secretary;
class Headmaster;
class Staff;
class Course;
class Room;

enum class ListType
{
    STUDENT,
    STAFF,
    COURSE,
    PROFESSOR,
    ROOM
};

template<typename T>
class IObjectList
{
    protected:
        /*
         * Should I keep type of lists?
        */
        // ListType _type;
        std::vector<std::shared_ptr<T>> _data;
        // std::shared_mutex _mutex;
        IObjectList() {}
    public:
        using object_type = std::shared_ptr<T>;
        static IObjectList<T>& getList()
        {
            /*
             * Used meyer's Singleton that is thread-safe
            */
            static IObjectList<T> instance;
            return instance;
        }
        // ListType getType() const
        // {
        //     return _type;
        // }
        void add(std::shared_ptr<T> elem)
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = std::find(_data.cbegin(), _data.cend(), elem);
            if (it == _data.cend())
                _data.emplace_back(elem);
            // implementation for add element
            
        }
        void remove(std::shared_ptr<T> elem)
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            if constexpr(std::is_same_v<T, Headmaster> || std::is_same_v<T, Secretary>)
                throw std::logic_error("Headmaster or Secreatary cannot be removed");
            auto it = std::find(_data.cbegin(), _data.cend(), elem);
            if (it != _data.cend())
                _data.erase(it);
            // implementation for remove element
        }
        /*
        * I think here can be better solution without using lambdas or functions
        */
        std::shared_ptr<T> get(std::function<bool(std::shared_ptr<T>)> condition) 
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            for(auto& item : _data)
                if (condition(item))
                    return item;
            return nullptr;
            // implementation for get element
        }
        std::shared_ptr<T> getFirst(std::function<bool(std::shared_ptr<T>)> condition)
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            std::shared_ptr<T> res;
            auto it = std::find_if(_data.begin(), _data.end(), condition);
            if (it != _data.end())
                res = *it;
            return res;
        }
        /*
		 * internal iterator for lists
		*/
        void apply(std::function<bool(std::shared_ptr<T>)> function)
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            for (auto elem : _data)
                function(elem);
        }
        std::size_t objCount() const
        {
            return _data.size();
        }
        /*
         * is returning all list good choice?
        */
        const std::vector<std::shared_ptr<T>>& getAll() const
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            return _data;
        }
};

/*
 * avoid inheritance
*/

using StudentList = IObjectList<Student>;
using StaffList = IObjectList<Staff>;
/*
 * Seperate professors for avoid dynamic_casts
*/
using ProfessorList = IObjectList<Professor>;
using CourseList = IObjectList<Course>;
using RoomList = IObjectList<Room>;



#if 0

    StudentList::getList().add(std::make_shared<Student>("Name0"));
    StudentList::getList().add(std::make_shared<Student>("Name1"));
    StudentList::getList().add(std::make_shared<Student>("Name2"));
    StudentList::getList().add(std::make_shared<Student>("Name3"));

    StudentList::getList().get(
    [&](Student_ptr st) -> bool
    {
        logic for get Student by criteria

    });


    StaffList::getList().add(std::make_shared<Staff>("Name0"));
    StaffList::getList().add(std::make_shared<Staff>("Name1"));
    StaffList::getList().add(std::make_shared<Staff>("Name2"));
    StaffList::getList().add(std::make_shared<Staff>("Name3"));

    StaffList::getList().get(
    [&](Staff_ptr st) -> bool
    {
        logic for get Staff by criteria

    });
    CourseList::getList().add(std::make_shared<Course>("Name0"));
    CourseList::getList().add(std::make_shared<Course>("Name1"));
    CourseList::getList().add(std::make_shared<Course>("Name2"));
    CourseList::getList().add(std::make_shared<Course>("Name3"));

    CourseList::getList().get(
    [&](Course_ptr st) -> bool
    {
        logic for get Course by criteria

    });
    ProfessorList::getList().add(std::make_shared<Course>("Name0"));
    ProfessorList::getList().add(std::make_shared<Course>("Name1"));
    ProfessorList::getList().add(std::make_shared<Course>("Name2"));
    ProfessorList::getList().add(std::make_shared<Course>("Name3"));

    ProfessorList::getList().get(
    [&](Professor_ptr pr) -> bool
    {
        logic for get Course by criteria

    });

    RoomList::getList().add(std::make_shared<Room>());
    RoomList::getList().add(std::make_shared<Classroom>());
    RoomList::getList().add(std::make_shared<Room>());
    RoomList::getList().add(std::make_shared<Room>());

    RoomList::getList().get(
    [&](Room_ptr st) -> bool
    {
        logic for get Room by criteria

    });

#endif

#endif