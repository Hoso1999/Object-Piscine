#ifndef __Triangle_HPP__
#define __Triangle_HPP__

#include "shape.hpp"
#include <iostream>

class Triangle : public Shape
{
    public:
        Triangle() {}

        void area()
        {
            std::cout << "Calculate Radius of Triangle" << std::endl;
        }

        void perimiter()
        {
            std::cout << "Calculate Radius of Triangle" << std::endl;
        }

};




#endif