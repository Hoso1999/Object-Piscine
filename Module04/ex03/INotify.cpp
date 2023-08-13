#include "INotify.hpp"
#include "Person.hpp"
#include "Room.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include "Headmaster.hpp"
#include "Form.hpp"

void SubscribeNotify::notify(sender_ptr p_sender, recieve_ptr p_reciever)
{

    if (p_sender && p_reciever)
    {
        p_sender->updateSubscribe(p_reciever);
        p_reciever->updateSubscribe(p_sender);
        std::cout << "Student " << p_sender->getName() << " get Course " << p_reciever->getName() << "\n";
    }
}

void UnsubscribeNotify::notify(sender_ptr p_sender, recieve_ptr p_reciever)
{

    if (p_sender && p_reciever)
    {
        p_sender->graduate(p_reciever);
        p_reciever->updateGraduate(p_sender);
        std::cout << "Student " << p_sender->getName() << " graduated Course " << p_reciever->getName() << "\n";
    }
}

void AssignNotify::notify(sender_ptr p_sender, recieve_ptr p_reciever)
{
        if (p_sender && p_reciever)
        {
            auto course = p_sender->currentCourse();
            if (course)
            {
                std::cout << "Professor " << p_sender->getName() << " closed Course " ;
                p_sender->closeCourse();
                // std::cout << c->getName() << "\n";
            }
            p_sender->updateCourse(p_reciever);
            p_reciever->updateResponsable(p_sender);
            std::cout << "Professor " << p_sender->getName() << " get Course " << p_reciever->getName() << "\n";
        }
}

void RoomEnterNotify::notify(sender_ptr p_sender, recieve_ptr p_reciever)
{

   
    if (p_sender && p_reciever && p_sender->canEnter(p_reciever))
    {
        p_reciever->exitRoom();
        p_sender->updateEnterPerson(p_reciever);
        p_reciever->updateEnterRoom(p_sender);
        std::cout << "Person " << p_reciever->getName() << " enter Room " << p_sender->getID() << "\n";
    }
}

void RoomExitNotify::notify(sender_ptr p_sender, recieve_ptr p_reciever)
{
  
    if (p_sender && p_reciever)
    {
        p_sender->updateExitPerson(p_reciever);
        p_reciever->updateExitRoom();
        std::cout << "Person " << p_reciever->getName() << " exit from Room " << p_sender->getID() << "\n";
    }
}
