#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>

#include "Block.hpp"

template <size_t Width, size_t Height>
class Map
{
public:
    Map()
    {
        for (size_t i = 0; i < Height; ++i)
        {
            for (size_t j = 0; j < Width; ++j)
            {
                map[i][j] = nullptr;
            }
        }
    }

    ~Map() = default;

    Map(Map&&) = delete;
    Map(const Map&) = delete;

    Map& operator=(Map&&) noexcept = delete;
    Map& operator=(const Map&) = delete;

    Block** operator[](size_t idx)
    {
        return map[idx];
    }

    const Block** operator[](size_t idx) const
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
    Block* map[Height][Width];
};

#endif