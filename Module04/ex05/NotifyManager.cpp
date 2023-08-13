#include "NotifyManager.hpp"
#include "RequestToHead.hpp"
#include <stdexcept>
#include <iostream>
#include <mutex>

void NotifyManager::addNotify(NotifyType type)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    _notifies[type] = create(type);
}

std::shared_ptr<INotifyBase> NotifyManager::create(NotifyType type)
{
    switch (type)
    {
        case NotifyType::AssignNotify:
            return std::make_shared<AssignNotify>();
        case NotifyType::SubscribeNotify:
            return std::make_shared<SubscribeNotify>();
        case NotifyType::RoomEnterNotify:
            return std::make_shared<RoomEnterNotify>();
        case NotifyType::RoomExitNotify:
            return std::make_shared<RoomExitNotify>();
        case NotifyType::NoCourseNotify:
            return std::make_shared<NoCourseNotify>();
        case NotifyType::NoClassNotify:
            return std::make_shared<NoClassNotify>();
        case NotifyType::GraduateNotify:
            return std::make_shared<GraduateNotify>();
        case NotifyType::JoinNotify:
            return std::make_shared<JoinCourseNotify>();
        case NotifyType::UnsubscribeNotify:
            return std::make_shared<UnsubscribeNotify>();
        default:
            return nullptr;
    }
    return nullptr;
}

