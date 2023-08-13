#ifndef __REQUESTTOHEAD_HPP__
#define __REQUESTTOHEAD_HPP__

#include "INotify.hpp"
#include "Form.hpp"
#include "Headmaster.hpp"

class Headmaster;

template<NotifyType notifyType, FormType type, typename T>
class RequestToHeadNotify : public INotify<notifyType, T, Headmaster>
{
    protected:
        using sender_ptr = T*;
        using recieve_ptr = Headmaster*;
    public:
        RequestToHeadNotify()
            :   INotify<notifyType, T, Headmaster>()
        {}
        void notify(sender_ptr p_sender, recieve_ptr p_reciever) override
        {
           if (p_sender && p_reciever)
            {
                auto form = p_reciever->recieveRequest(type);
                std::cout << "recive form " << ((int)form->getType()) << "\n";
                p_sender->fillForm(form);
                p_reciever->receiveForm(form);
                bool isSigned = p_reciever->confirm(form);
                p_sender->update(isSigned);
            }
        }
};

using NoCourseNotify = RequestToHeadNotify<NotifyType::NoCourseNotify, FormType::NeedCourseCreation, Professor>;
using NoClassNotify = RequestToHeadNotify<NotifyType::NoClassNotify, FormType::NeedMoreClassRoom, Professor>;
using GraduateNotify = RequestToHeadNotify<NotifyType::GraduateNotify, FormType::CourseFinished, Professor>;
using JoinCourseNotify = RequestToHeadNotify<NotifyType::JoinNotify, FormType::SubscriptionToCourse, Student>;

#endif