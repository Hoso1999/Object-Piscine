#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main(int argc, char const *argv[])
{
    Triangle triangle;
    Circle circle;
    Rectangle rect;

    triangle.area();
    triangle.perimiter();
    circle.area();
    circle.perimiter();
    rect.area();
    rect.perimiter();
    /* code */
    return 0;
}
