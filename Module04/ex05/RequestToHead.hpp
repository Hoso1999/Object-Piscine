#ifndef __REQUESTTOHEAD_HPP__
#define __REQUESTTOHEAD_HPP__

#include "INotify.hpp"
#include "Form.hpp"
#include "Headmaster.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include <mutex>

class Headmaster;
/*
 * Interface for Headmaster requests
 * avoid dublicate code used template instead for Student and Professor
*/
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
            static std::mutex m;
            std::lock_guard<std::mutex> guard(m);
            if (p_sender && p_reciever)
            {
                auto form = p_reciever->recieveRequest(type);
                std::cout << "Request To Headmaster with [ Form ] [ " << ((int)form->getType()) << " ]" << std::endl;
                p_sender->fillForm(form);
                p_reciever->receiveForm(form);
                bool isSigned = p_reciever->confirm(form);
                p_sender->updateSigned(isSigned, form->getType());
            }
        }
};
/*
 * avoid inheritance it can done without it
*/
using NoCourseNotify = RequestToHeadNotify<NotifyType::NoCourseNotify, FormType::NeedCourseCreation, Professor>;
using NoClassNotify = RequestToHeadNotify<NotifyType::NoClassNotify, FormType::NeedMoreClassRoom, Professor>;
using GraduateNotify = RequestToHeadNotify<NotifyType::GraduateNotify, FormType::CourseFinished, Professor>;
using JoinCourseNotify = RequestToHeadNotify<NotifyType::JoinNotify, FormType::SubscriptionToCourse, Student>;

#endif