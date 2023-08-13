#include "NotifyManager.hpp"
#include <stdexcept>
#include <iostream>


void NotifyManager::addNotify(std::shared_ptr<INotifyBase> p_notify)
{
    if (p_notify)
        _notifies[p_notify->getType()] = p_notify;
}
 std::shared_ptr<INotifyBase> NotifyManager::getNotify(NotifyType p_type) const
{
    auto it = _notifies.find(p_type);
    if (it == _notifies.end())
        throw std::logic_error("no such notify type");
    return it->second;
}