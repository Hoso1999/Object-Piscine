#include "Room.hpp"
#include "Person.hpp"
#include "Staff.hpp"
#include "NotifyManager.hpp"

long long Room::_id = 0;

void Room::enter(Person* p_person)
{
    auto _enterNotify = _notifyManager->getNotify(NotifyType::RoomEnterNotify);
    auto enterNotify = std::dynamic_pointer_cast<RoomEnterNotify>(_enterNotify);
    if (enterNotify)
        enterNotify->notify(this, p_person);
}
void Room::updateEnterPerson(Person* p_person)
{
    auto it = std::find_if(_occupants.begin(), _occupants.end(),
    [&](Person* p)
    {
        return (p && p_person && p == p_person);
    });
    if (it == _occupants.end())
        _occupants.emplace_back(p_person);
    else
        *it = p_person;
}
void Room::updateExitPerson(Person* p_person)
{
   auto it = std::find_if(_occupants.cbegin(), _occupants.cend(),
   [&](Person* p)
   {
        return (p && p_person && p_person == p);
   });
   if (it != _occupants.cend())
    _occupants.erase(it);
}

void Room::exit(Person* p_person)
{
    auto _exitNotify = _notifyManager->getNotify(NotifyType::RoomExitNotify);
    auto exitNotify = std::dynamic_pointer_cast<RoomExitNotify>(_exitNotify);
    if (exitNotify)
        exitNotify->notify(this, p_person);
}