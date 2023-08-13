#ifndef __ILIST_HPP__
#define __ILIST_HPP__

#include <list>
#include <shared_mutex>
#include <memory>
#include <functional>
#include <algorithm>

class Student;
class Staff;
class Course;
class Room;

// enum class ListType
// {
//     STUDENT,
//     STAFF,
//     CourseList,
//     RoomList
// };

template<typename T>
class IObjectList
{
    protected:
        /*
         * Should I keep type of lists?
        */
        // ListType _type;
        std::list<std::shared_ptr<T>> _data;
        // std::shared_mutex _mutex;
        IObjectList() {}
    public:
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
            auto it = std::find(_data.cbegin(), _data.cend(), elem);
            if (it != _data.cend())
                _data.erase(it);
            // implementation for remove element
        }
        /*
        * I think here can be better solution without using lambdas or functions
        */
        std::shared_ptr<T> get(std::function<bool(std::shared_ptr<T>&)> condition) 
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            for(auto& item : _data)
                if (condition(item))
                    return item;
            return nullptr;
            // implementation for get element
        }
        std::shared_ptr<T> getFirst(std::function<bool(std::shared_ptr<T>&)> condition)
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            std::shared_ptr<T> res;
            auto it = std::find_if(_data.begin(), _data.end(),
            [&](std::shared_ptr<T> elem)
            {
                return condition(elem);
            });
            if (it != _data.end())
                res = *it;
            return res;
        }

        void apply(std::function<bool(std::shared_ptr<T>&)> function)
        {
            static std::mutex _mutex;
            std::lock_guard<std::mutex> lock(_mutex);
            for (auto elem : _data)
                function(elem);
        }
        /*
         * is returning all list good choice?
        */
        const std::list<std::shared_ptr<T>>& getAll() const
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

    RoomList::getList().add(std::make_shared<Room>("Name0"));
    RoomList::getList().add(std::make_shared<Room>("Name1"));
    RoomList::getList().add(std::make_shared<Room>("Name2"));
    RoomList::getList().add(std::make_shared<Room>("Name3"));

    RoomList::getList().get(
    [&](Room_ptr st) -> bool
    {
        logic for get Room by criteria

    });

#endif

#endif