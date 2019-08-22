#ifndef IO_INTERFACE_HPP
#define IO_INTERFACE_HPP

#include "Enums.hpp"

class IOInterface
{
public:
    virtual MoveType Move() = 0;
};

#endif