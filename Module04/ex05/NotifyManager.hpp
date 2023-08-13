#ifndef __NOTIFYMANAGER_HPP__
#define __NOTIFYMANAGER_HPP__

#include "INotify.hpp"
#include <unordered_map>
#include <mutex>


/*
* maybe have template notify manager will be better
* for avoid dynamic_casts
*/
class NotifyManager
{
    private:
        /*
         * maybe use std::variant for pointers to avoid dynamic_casts
        */
        std::unordered_map<NotifyType, std::shared_ptr<INotifyBase>> _notifies;
        NotifyManager()
        {}
    public:
        /*
         * i think its not good solution but it works
        */
        static NotifyManager& getNotifyManager()
        {
            static NotifyManager manager;
            return manager;
        }
        void addNotify(NotifyType type);
        /*
         * factory for Notify types
        */
        std::shared_ptr<INotifyBase> create(NotifyType type);
       
        /*
         * get notify associated with NotifyType
        * I think it bad variant we should use dynamic_casts
        */
        template<typename T>
        std::shared_ptr<T> getNotify(NotifyType p_type) const
        {
            static std::mutex m;
            std::lock_guard<std::mutex> guard(m);
            auto it = _notifies.find(p_type);
            if (it == _notifies.end())
                throw std::logic_error("no such notify type");
            return std::dynamic_pointer_cast<T>(it->second);
        }
        // std::shared_ptr<INotifyBase> getNotify(NotifyType p_type) const;
};



#endif