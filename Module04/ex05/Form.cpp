#include "Form.hpp"
#include "Staff.hpp"
#include "Student.hpp"
#include "IObjectList.hpp"
#include "Room.hpp"
#include "Professor.hpp"
#include "Course.hpp"
#include "Wrappers.hpp"

bool CourseFinishedForm::validate()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    return _finished;
}

void CourseFinishedForm::execute()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    std::cout << "Student [ " << _student->getName() << " ] is graduated" << std::endl;
    _student->exitClass();
    // _responsable->closeCourse();
}

void NeedMoreClassRoomForm::execute()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto classroom = std::make_shared<Classroom>();
    RoomList::getList().add(classroom);
    std::cout << "Created new Classroom" << std::endl;
}

bool NeedMoreClassRoomForm::validate()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    return _course && _course->hasResponsable();
}


void NeedCourseCreationForm::execute()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto newCourse = std::make_shared<Course>(_subject);
    std::size_t count = Operation<StudentList>::objCount() * 1./5.;
    std::size_t required = Operation<CourseList>::objCount() * 1./8.;
    newCourse->setMaximumStudents(count);
    newCourse->setRequiredClasses(required);
    newCourse->assign(_professor);
    Operation<CourseList>::add(newCourse);
    std::cout << "New Course Created" << std::endl;
}

bool NeedCourseCreationForm::validate()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
	return  !(_professor && _professor->hasCourse());
}

void SubscriptionToCourseForm::execute()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto subscribeNotify = std::make_shared<SubscribeNotify>();
    _course->subsribe(_student);
    std::cout << "Student [ " << _student->getName() << " ] subsribed to [ " << _course->getName() << " ] Course" << std::endl;
}
bool SubscriptionToCourseForm::validate()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    return _course && !(_course->isFull() || _course->hasStudent(_student));
}


