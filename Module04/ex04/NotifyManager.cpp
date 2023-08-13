#include "NotifyManager.hpp"
#include <stdexcept>
#include <iostream>
#include <mutex>

void NotifyManager::addNotify(std::weak_ptr<INotifyBase> p_notify)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    if (!p_notify.expired())
    {
        auto notify = p_notify.lock();
        if (notify)
            _notifies[notify->getType()] = notify;
    }
}
 std::shared_ptr<INotifyBase> NotifyManager::getNotify(NotifyType p_type) const
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    auto it = _notifies.find(p_type);
    if (it == _notifies.end())
        throw std::logic_error("no such notify type");
    return it->second;
}