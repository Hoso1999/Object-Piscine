#ifndef __NOTIFYMANAGER_HPP__
#define __NOTIFYMANAGER_HPP__

#include "INotify.hpp"
// #include "RequestToHead.hpp"
#include <unordered_map>

class NotifyManager
{
    private:
        std::unordered_map<NotifyType, std::shared_ptr<INotifyBase>> _notifies;
        NotifyManager()
        {}
    public:
        static NotifyManager& getNotifyManager()
        {
            static NotifyManager manager;
            return manager;
        }
        void addNotify(std::weak_ptr<INotifyBase> p_notify);
       
        std::shared_ptr<INotifyBase> getNotify(NotifyType p_type) const;
};



#endif