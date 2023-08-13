#ifndef __OBSERVER_HPP__
#define __OBSERVER_HPP__

#include "Event.hpp"
#include <list>
#include <memory>
#include <chrono>
#include <thread>
#include <algorithm>
#include <mutex>
#include <future>


/*
 * Listeners for Bellsystem
 * every subject should inherit from it
*/
class Listener
{
    public:
        Listener() {}
        virtual ~Listener() {}
        virtual void update(Event event) = 0;
};

class BellSystem
{
    private:
        const int               _duration;
        bool                    _freeTime;
        std::list<Listener*>    _listeners;

        void notifyListeners(Event event)
        {
            static std::mutex m;
            std::lock_guard<std::mutex> guard(m);
            for (auto listener : _listeners)
            {
                auto as = std::async([&](){
                    listener->update(event);
                });

            }
        }
    public:
        BellSystem(int p_duration = 5)
            :   _duration(p_duration),
                _freeTime(false)
        {}
        void addListener(Listener* p_listener)
        {
            static std::mutex m;
            std::lock_guard<std::mutex> guard(m);
            _listeners.push_back(p_listener);
        }

        bool isFreeTime()
        {
            static std::mutex m;
            std::lock_guard<std::mutex> guard(m);
            return _freeTime;
        }
        void removeListener(Listener* p_listener)
        {
            static std::mutex m;
            std::lock_guard<std::mutex> guard(m);
            _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), p_listener), _listeners.end());
        }
        void start()
        {
            static std::mutex m;
            std::lock_guard<std::mutex> guard(m);
            _freeTime = true;
            std::cout << "[Bell] Ringing. Its free time" << std::endl;
            notifyListeners(Event::RingBell);
            std::this_thread::sleep_for(std::chrono::seconds(_duration));
            _freeTime = false;
            std::cout << "[Bell] Ringing. Its class time" << std::endl;
            notifyListeners(Event::RingBell);
        }
};



#endif