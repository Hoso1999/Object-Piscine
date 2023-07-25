#include "Info.hpp"

Position::Position(int p_x, int p_y, int p_z)
    :   x(p_x),
        y(p_y),
        z(p_z)
{}

int Position::getX() const
{
    return x;
}

int Position::getY() const
{
    return y;
}

int Position::getZ() const
{
    return z;
}

void Position::setX(int p_x)
{
    x = p_x;
}

void Position::setY(int p_y)
{
    y = p_y;
}

void Position::setZ(int p_z)
{
   z = p_z;
}

Statistic::Statistic(int p_level, int p_exp)
    :   level(p_level),
        exp(p_exp)
{}

int Statistic::getExp() const
{
    return exp;
}

int Statistic::getLevel() const
{
    return level;
}

void Statistic::setExp(int p_exp)
{
    exp = p_exp;
}

void Statistic::setLevel(int p_level)
{
    level = p_level;
}