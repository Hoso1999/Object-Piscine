#include "Form.hpp"
#include "Staff.hpp"
#include "Student.hpp"
#include "IObjectList.hpp"
#include "Room.hpp"
#include "Professor.hpp"
#include "Course.hpp"

bool CourseFinishedForm::validate()
{
    return _finished;
}

void CourseFinishedForm::execute()
{

    std::cout << "Student " << _student->getName() << " is graduated\n";
    _student->exitClass();
    // _responsable->closeCourse();
}

void NeedMoreClassRoomForm::execute()
{
    auto classroom = std::make_shared<Classroom>();
    // classroom->addNotify(std::make_shared<RoomEnterNotify>());
    // classroom->addNotify(std::make_shared<RoomExitNotify>());
    classroom->assignCourse(_course);
    RoomList::getList().add(classroom);
    std::cout << "Created new Classroom\n";
}

bool NeedMoreClassRoomForm::validate()
{
    return _course->hasResponsable();
}


void NeedCourseCreationForm::execute()
{
    auto newCourse = std::make_shared<Course>(_subject);
    newCourse->setMaximumStudents(10);
    // auto assignNotify = std::make_shared<AssignNotify>();
    // auto subscribeNotify = std::make_shared<SubscribeNotify>();
    // newCourse->addNotify(assignNotify);
    // newCourse->addNotify(subscribeNotify);
    newCourse->assign(_professor);
    int i = 0;
    CourseList::getList().add(newCourse);
    // StudentList::getList().apply(
    // [&](std::shared_ptr<Student> st) -> bool
    // {
    //     if (st->numberOfClasses() < newCourse->numberClassToGraduate() && i < 5)
    //     {
    //         // st->addNotify(assignNotify);
    //         // st->addNotify(subscribeNotify);
    //         st->subcribe(newCourse);
    //         ++i;
    //     }
    //     return true;
    // });
    std::cout << "New Course Created\n";
}

bool NeedCourseCreationForm::validate()
{
	return !(_professor && _professor->hasCourse());
}

void SubscriptionToCourseForm::execute()
{
    auto subscribeNotify = std::make_shared<SubscribeNotify>();
    // _course->addNotify(subscribeNotify);
    // _student->addNotify(subscribeNotify);
    _course->subsribe(_student);
    std::cout << "Student " << _student->getName() << " subsribed to " << _course->getName() << " Course\n";
}
bool SubscriptionToCourseForm::validate()
{
    return !(_course->isFull() || _course->hasStudent(_student));
}


