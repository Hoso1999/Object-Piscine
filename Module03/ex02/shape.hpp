#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

class Shape
{
    public:
        Shape() {}
        virtual ~Shape() {}
        virtual void area() = 0;
        virtual void perimiter() = 0;
};

#endif