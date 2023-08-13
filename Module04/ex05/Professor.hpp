#ifndef __PROFESSOR_HPP__
#define __PROFESSOR_HPP__

#include "Staff.hpp"
#include <queue>
#include <unordered_map>
#include "NotifyManager.hpp"
#include "observer.hpp"

class AssignNotify;
class Secretary;
enum class NotifyType;
class Classroom;

/*
 * inherits from Listener because should notifed on events
 * maybe inherit from Listener with private mode?
*/
class Professor : public Staff, public Listener
{
    private:
        /*
         * can professor assigned to multiple courses?
        */
        Course*               _currentCourse;
        std::queue<Student*>  _requests;
        Room*                 _lastRoom;
        BellSystem*           _bellSystem;

        void searchEmptyRoom(Classroom* p_currentClass, Course* p_course);
    public:
        Professor(std::string p_name)
            :	Staff(p_name, PersonType::PROFESSOR),
                _bellSystem(nullptr),
                _lastRoom(nullptr),
                _currentCourse(nullptr)
        {}
        void assignCourse(Course* p_course);

        void setBellSystem(BellSystem* p_bell);
        bool hasCourse() const
        {
            return _currentCourse;
        }
        void updateCourse(Course* p_course)
        {
            _currentCourse = p_course;
        }
       
        Course* currentCourse()
        {
            return _currentCourse;
        }
        /*
         * update professor object on event
        */
        void update(Event p_event) override;
        void sendRequest(FormType p_type);
        /*
         * no need to check if student already exists in queue
         * professor can get request from same student
        */
        void recieveRequest(Student* p_student)
        {
            _requests.push(p_student);
        }
        void fillForm(std::shared_ptr<Form> p_form);
        /*
         * update professor when form is signed by headmaster
        */
        void updateSigned(bool isSigned, FormType type);
        void doClass();
        void closeCourse();
};

using Professor_ptr = std::shared_ptr<Professor>;


#endif