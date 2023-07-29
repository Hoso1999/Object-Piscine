#include "Car.hpp"


int main(int argc, char const *argv[])
{
    Car car;

    car.start();
    car.accelerate(6.7);
    car.shift_gears_up();
    car.shift_gears_up();
    car.shift_gears_down();
    car.turn_wheel(4.5);
    car.straighten_wheels();
    car.stop();
    car.apply_force_on_brakes(6.8);
    car.start();
    car.accelerate(6.7);
    car.shift_gears_up();
    car.shift_gears_up();
    car.shift_gears_down();
    car.stop();
    car.apply_emergency_brakes();
    car.start();
    car.reverse();
    car.accelerate(9.8);
    car.stop();
    return 0;
}
