#include "FormFactory.hpp"
#include "Form.hpp"

std::shared_ptr<Form> FormFactory::createForm(FormType type)
{
    switch (type)
    {
        case FormType::CourseFinished:
            return std::make_shared<CourseFinishedForm>();
        case FormType::NeedMoreClassRoom:
            return std::make_shared<NeedMoreClassRoomForm>();
        case FormType::NeedCourseCreation:
            return std::make_shared<NeedCourseCreationForm>();
        case FormType::SubscriptionToCourse:
            return std::make_shared<SubscriptionToCourseForm>();
        default:
            return nullptr;
    }
    return nullptr;
}