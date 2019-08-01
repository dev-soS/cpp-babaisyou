#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <map>
#include <vector>

#include "Enums.hpp"
#include "Map.hpp"

namespace Algorithm
{
std::tuple<bool, size_t, size_t> next(std::tuple<size_t, size_t> pos,
                                      std::tuple<size_t, size_t> size,
                                      MoveType direction)
{
    static std::map<MoveType, std::tuple<int, int>> deltas =
    {
        { MoveType::UP, { 0, 1 } },
        { MoveType::DOWN, { 0, -1 } },
        { MoveType::LEFT, { -1, 0, } },
        { MoveType::RIGHT, { 1, 0, } },
    };

    auto[x, y] = pos;
    auto[width, height] = size;
    auto[dx, dy] = deltas[direction];

    int new_x = static_cast<int>(x) + dx;
    int new_y = static_cast<int>(y) + dy;

    auto valid = [](int src, int range) { return 0 <= src && src < range; };
    return std::make_tuple(valid(new_x, width) && valid(new_y, height), new_x, new_y);
}

template <size_t Width, size_t Height>
std::tuple<bool, size_t, size_t> movable(const Map<Width, Height>& map,
                                         std::tuple<size_t, size_t> pos,
                                         MoveType direction)
{
    auto[x, y] = pos;
    std::unique_ptr<Block>& current = map[y][x];
    // TODO: Add property not only push, but also move etc.
    if (!current->containProperty(Property::PUSH))
    {
        return std::make_tuple(false, 0, 0);
    }

    auto[possible, new_x, new_y] = next(pos, std::make_tuple(Width, Height), direction);
    if (!possible) 
    {
        return std::make_tuple(false, 0, 0);
    }

    std::unique_ptr<Block>& block = map[new_y][new_x];
    bool possible = block == nullptr || !block->containProperty(Property::STOP);
    return std::make_tuple(possible, new_x, new_y);
}

template <size_t Width, size_t Height>
bool move(Map<Width, Height>& map, std::tuple<size_t, size_t> pos, MoveType direction)
{
    auto[x, y] = pos;
    auto[possible, new_x, new_y] = movable(map, pos, direction);
    if (possible)
    {
        move(map, std::make_tuple(new_x, new_y), direction);
        map[new_y][new_x] = std::move(map[x, y]);
        return true;
    }
    return false;
}

void update_blocks(std::vector<Block*> blocks)
{
    
}

template <size_t Width, size_t Height>
void update(Map<Width, Height>& map)
{

}
}

#endif