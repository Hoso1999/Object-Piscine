#ifndef __VECTOR2_HPP__
#define __VECTOR2_HPP__

class Vector2
{
    private:
        float x_;
        float y_;
    public:
        Vector2(float x = 0, float y = 0)
            :   x_(x), y_(y)
        {}

        void setX(float x)
        {
            x_ = x;
        }

        void setY(float y)
        {
            y_ = y;
        }

        float getX() const
        {
            return x_;
        }
        
        float getY() const
        {
            return y_;
        }
};



#endif