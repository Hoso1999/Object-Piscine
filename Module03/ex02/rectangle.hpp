#ifndef __RECTANGLE_HPP__
#define __RECTANGLE_HPP__

#include "shape.hpp"
#include <iostream>

class Rectangle : public Shape
{
    public:
        Rectangle() {}

        void area()
        {
            std::cout << "Calculate Radius of Rectangle" << std::endl;
        }

        void perimiter()
        {
            std::cout << "Calculate Radius of Rectangle" << std::endl;
        }

};




#endif