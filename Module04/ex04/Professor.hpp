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

class Professor : public Staff, public Listener
{
private:
	/*
	 * is professor can be assigned to multiple courses?
	*/
	Course*                     _currentCourse;
    std::queue<Student*>        _requests;
    Room*                       _lastRoom;
    std::weak_ptr<BellSystem>   _bellSystem;

public:
	Professor(std::string p_name)
		:	Staff(p_name, PersonType::PROFESSOR)
	{}
	void assignCourse(Course* p_course);

    void setBellSystem(std::weak_ptr<BellSystem> p_bell);
    bool hasCourse() const
    {
        return _currentCourse;
    }
    void updateCourse(Course* p_course)
    {
        _currentCourse = p_course;
    }
    /*
     * can shared_ptr work here?
    */
    // void needToGraduate(std::shared_ptr<Student> p_student);
    Course* currentCourse()
    {
        return _currentCourse;
    }
    void update(Event p_event) override;
    void sendRequest(FormType p_type);
    void fillForm(std::shared_ptr<Form> p_form);
    void updateSigned(bool isSigned);
    // void update();
	void doClass();
	void closeCourse();
};

using Professor_ptr = std::shared_ptr<Professor>;


#endif