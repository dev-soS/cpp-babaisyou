#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "Block.hpp"

template <size_t Width, size_t Height>
class Map
{
public:
    Map() = default;
    ~Map() = default;

    Map(Map&&) = delete;
    Map(const Map&) = delete;

    Map& operator=(Map&&) noexcept = delete;
    Map& operator=(const Map&) = delete;

    std::vector<Block*>* operator[](size_t idx)
    {
        return map[idx];
    }

    const std::vector<Block*>* operator[](size_t idx) const
    {
        return map[idx];
    }

    size_t getWidth() const
    {
        return Width;
    }

    size_t getHeight() const 
    {
        return Height;
    }

    
private:
    std::vector<Block*> map[Height][Width];
};

#endif