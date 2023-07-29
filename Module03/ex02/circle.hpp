#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "shape.hpp"
#include <iostream>

class Circle : public Shape
{
    public:
        Circle() {}

        void area()
        {
            std::cout << "Calculate Radius of Circle" << std::endl;
        }

        void perimiter()
        {
            std::cout << "Calculate Radius of Circle" << std::endl;
        }

};




#endif