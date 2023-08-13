#include "Form.hpp"
#include "Staff.hpp"
#include "Student.hpp"
#include "IObjectList.hpp"
#include "Room.hpp"
#include "Professor.hpp"
#include "Course.hpp"

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

    std::cout << "Student " << _student->getName() << " is graduated\n";
    _student->exitClass();
    // _responsable->closeCourse();
}

void NeedMoreClassRoomForm::execute()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto classroom = std::make_shared<Classroom>();
    classroom->assignCourse(_course);
    RoomList::getList().add(classroom);
    std::cout << "Created new Classroom\n";
}

bool NeedMoreClassRoomForm::validate()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    return _course->hasResponsable();
}


void NeedCourseCreationForm::execute()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto newCourse = std::make_shared<Course>(_subject);
    newCourse->setMaximumStudents(10);
    newCourse->assign(_professor);
    int i = 0;
    CourseList::getList().add(newCourse);
    std::cout << "New Course Created\n";
}

bool NeedCourseCreationForm::validate()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
	return !(_professor && _professor->hasCourse());
}

void SubscriptionToCourseForm::execute()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto subscribeNotify = std::make_shared<SubscribeNotify>();
    _course->subsribe(_student);
    std::cout << "Student " << _student->getName() << " subsribed to " << _course->getName() << " Course\n";
}
bool SubscriptionToCourseForm::validate()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    return !(_course->isFull() || _course->hasStudent(_student));
}


