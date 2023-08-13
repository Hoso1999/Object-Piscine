#ifndef __PROFESSOR_HPP__
#define __PROFESSOR_HPP__

#include "Staff.hpp"
#include <queue>
#include <unordered_map>
#include "NotifyManager.hpp"

class AssignNotify;
class Secretary;
enum class NotifyType;

class Professor : public Staff
{
private:
	/*
	 * is professor can be assigned to multiple courses?
	*/
	Course*               _currentCourse;
    std::queue<Student*>  _requests;

public:
	Professor(std::string p_name)
		:	Staff(p_name, PersonType::PROFESSOR)
	{}
	void assignCourse(Course* p_course);

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
    void sendRequest(FormType p_type);
    void fillForm(std::shared_ptr<Form> p_form);
    void update(bool isSigned);
    // void update();
	void doClass();
	void closeCourse();
};

using Professor_ptr = std::shared_ptr<Professor>;


#endif