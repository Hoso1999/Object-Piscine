#include "Room.hpp"
#include "Person.hpp"
#include "Staff.hpp"
#include "NotifyManager.hpp"
#include <mutex>

long long Room::_id = 0;

Room::Room(RoomType p_type)
    :	ID(_id),
        _type(p_type),
       _notifyManager(NotifyManager::getNotifyManager())
{
    ++Room::_id;
}

void Room::enter(Person* p_person)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto enterNotify = _notifyManager.getNotify<RoomEnterNotify>(NotifyType::RoomEnterNotify);
    if (enterNotify)
        enterNotify->notify(this, p_person);
}
void Room::updateEnterPerson(Person* p_person)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
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
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
   auto it = std::find_if(_occupants.cbegin(), _occupants.cend(),
   [&](Person* p)
   {
        return (p && p_person && p == p_person);
   });
   if (it != _occupants.cend())
    _occupants.erase(it);
}


void Room::exit(Person* p_person)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    auto exitNotify = _notifyManager.getNotify<RoomExitNotify>(NotifyType::RoomExitNotify);
    if (exitNotify)
        exitNotify->notify(this, p_person);
   
}