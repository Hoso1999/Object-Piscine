#include "Person.hpp"
#include "Room.hpp"
#include "Course.hpp"
#include "NotifyManager.hpp"
#include <mutex>

void Person::enterRoom(Room* p_room)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto _enterNotify = _notifyManager.getNotify(NotifyType::RoomEnterNotify);

    auto enterNotify = std::dynamic_pointer_cast<RoomEnterNotify>(_enterNotify);
    if (enterNotify)
        enterNotify->notify(p_room, this);
}

void Person::exitRoom()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto _exitNotify = _notifyManager.getNotify(NotifyType::RoomExitNotify);
    auto exitNotify =  std::dynamic_pointer_cast<RoomExitNotify>(_exitNotify);
    if (exitNotify)
        exitNotify->notify(_currentRoom, this);
}