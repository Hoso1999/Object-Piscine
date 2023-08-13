#include "Person.hpp"
#include "Room.hpp"
#include "Course.hpp"
#include "NotifyManager.hpp"


void Person::enterRoom(Room* p_room)
{

    auto _enterNotify = _notifyManager.getNotify(NotifyType::RoomEnterNotify);
    auto enterNotify = std::dynamic_pointer_cast<RoomEnterNotify>(_enterNotify);
    if (enterNotify)
        enterNotify->notify(p_room, this);
}

void Person::exitRoom()
{
    auto _exitNotify = _notifyManager.getNotify(NotifyType::RoomExitNotify);

    auto exitNotify =  std::dynamic_pointer_cast<RoomExitNotify>(_exitNotify);
    if (exitNotify)
        exitNotify->notify(_currentRoom, this);
}