#include "Form.hpp"
#include "Staff.hpp"
#include "IObjectList.hpp"

void CourseFinishedForm::execute()
{
    std::cout << "Course " << _course->getName() << " is finished\n";
}

void NeedMoreClassRoomForm::execute()
{
    std::cout << "New classroom needed\n";
}


void NeedCourseCreationForm::execute()
{
    auto newCourse = std::make_shared<Course>(_subject);
    newCourse->assign(_professor);
    CourseList::getList().add(newCourse);
    std::cout << "New Course needed\n";
}

void SubscriptionToCourseForm::execute()
{
    _course->subscribe(_student);
    std::cout << "Student " << _student->getName() << " subsribed to " << _course->getName() << " Course\n";
}


void Staff::sign(Form_ptr p_form)
{
    p_form->execute();
}