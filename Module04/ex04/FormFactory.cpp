#include "FormFactory.hpp"
#include "Form.hpp"
#include <mutex>

std::shared_ptr<Form> FormFactory::createForm(FormType type)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
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