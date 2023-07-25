#ifndef __INFO_HPP__
#define __INFO_HPP__


class Position
{
    private:
        int x;
        int y;
        int z;
    public:
        Position(int p_x, int p_y, int p_z);
        int getX() const;
        int getY() const;
        int getZ() const;
        void setX(int p_x);
        void setY(int p_y);
        void setZ(int p_z);
};

class Statistic
{
    private:
        int level;
        int exp;
    public:
        Statistic(int p_level, int p_exp);
        int getLevel() const;
        int getExp() const;
        void setLevel(int p_level);
        void setExp(int p_exp);
};

#endif