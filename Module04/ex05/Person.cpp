#include "Person.hpp"
#include "Room.hpp"
#include "Course.hpp"
#include "NotifyManager.hpp"
#include <mutex>

void Person::enterRoom(Room* p_room)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto enterNotify = _notifyManager.getNotify<RoomEnterNotify>(NotifyType::RoomEnterNotify);
    if (enterNotify)
        enterNotify->notify(p_room, this);
}

void Person::exitRoom()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto exitNotify = _notifyManager.getNotify<RoomExitNotify>(NotifyType::RoomExitNotify);
    if (exitNotify)
        exitNotify->notify(_currentRoom, this);
}