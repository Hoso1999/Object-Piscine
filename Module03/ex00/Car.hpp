#ifndef CAR_HPP
#define CAR_HPP

#include "Engine.hpp"
#include "Wheel.hpp"
#include "Controller.hpp"
#include "Gear.hpp"


class Car
{
    Engine      m_engine;
    Controller  m_controller;
    Gear        m_gear;
    Wheel       m_wheel;

    public:
        Car() {}
    
        void start()
        {
            m_engine.start();
        }

        void stop()
        {
            m_engine.stop();
        }

        void turn_wheel( float angle )
        {
            m_wheel.turn_wheel(angle);
        }

        void straighten_wheels()
        {
            m_wheel.straighten_wheels();
        }
    
        void shift_gears_up()
        {
            m_gear.shift_gears_up();
        }

        void shift_gears_down()
        {
            m_gear.shift_gears_down();
        }

        void accelerate( float speed )
        {
            m_controller.accelerate(speed);
        }

        void apply_force_on_brakes( float force )
        {
            m_controller.apply_force_on_brakes(force);
        }

        void reverse()
        {
            m_gear.reverse();
        }
    
        void apply_emergency_brakes()
        {
            m_controller.apply_emergency_brakes();
        }
};



#endif