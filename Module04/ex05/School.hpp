#ifndef __SCHOOL_HPP__
#define __SCHOOL_HPP__

#include "NotifyManager.hpp"
#include "Headmaster.hpp"
#include "Staff.hpp"
#include "IObjectList.hpp"
#include <uuid/uuid.h>
#include "Professor.hpp"
#include "Student.hpp"
#include "Room.hpp"
#include <string>
#include <future>
#include "Wrappers.hpp"

/*
 * listManager for 
*/
class ListManager
{
    std::shared_ptr<Headmaster>     _head;
    std::shared_ptr<Secretary>      _secretary;
    private:
        std::string generateRandomID();
    public:
        ListManager();
        void recruteProfessor()
        {
            auto prof = std::make_shared<Professor>(generateRandomID());
            Operation<ProfessorList>::add(prof);
        }
        inline void recruteStudent()
        {
            Operation<StudentList>::add(std::make_shared<Student>(generateRandomID()));
        }
        
        Course_ptr getCourse(std::string p_name) const;

        inline std::vector<Professor_ptr> getProfessors() const
        {
            return Operation<ProfessorList>::getAll();
        }
        inline std::shared_ptr<Headmaster> getHeadmaster() const
        {
            return _head;
        }
        inline std::shared_ptr<Secretary> getSecretary() const
        {
            return _secretary;
        }
};


class School
{
private:
    NotifyManager&                  _manager;
    std::unique_ptr<ListManager>    _listManager;
    std::shared_ptr<BellSystem>     _bellSystem;
   
   
    template<typename List>
    void registerBellSystem()
    {
        Lambda<List>::apply(
        [&](typename List::object_type obj) -> bool
        {
            if (obj)
                obj->setBellSystem(_bellSystem.get());
            return true;
        });
    }
    public:
        School();
        void runDayRoutine();

        void graduationCeremony();

        inline void launchClasses()
        {
            _listManager->getHeadmaster()->startCourses();
        }
        inline void requestRingBell()
        {
            _listManager->getHeadmaster()->ringTheBell();
        }
        inline void recruteProfessor()
        {
            _listManager->recruteProfessor();
        }
        inline void recruteStudent()
        {
            _listManager->recruteStudent();
        }
        inline Course_ptr getCourse(std::string p_name) const
        {
            return _listManager->getCourse(p_name);
        }
        inline std::vector<Professor_ptr> getProfessors() const
        {
            return _listManager->getProfessors();
        }

        inline std::shared_ptr<Headmaster> getHeadmaster() const
        {
            return  _listManager->getHeadmaster();
        }
        inline std::shared_ptr<Secretary> getSecretary() const
        {
            return _listManager->getSecretary();
        }
};



#endif