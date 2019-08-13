#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <map>
#include <optional>
#include <vector>

#include "Block.hpp"
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
    const std::unique_ptr<Block>& current = map[y][x];
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

    const std::unique_ptr<Block>& block = map[new_y][new_x];
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
        // TODO: Replace map element type from std::unique_ptr<Block> to std::vector<std::unique_ptr<Block>>
        // TODO: Move specified block (ex. float)
        move(map, std::make_tuple(new_x, new_y), direction);
        map[new_y][new_x] = std::move(map[y][x]);
        return true;
    }
    return false;
}

void update_blocks(const std::vector<Block*>& blocks)
{
    if (blocks.size() % 2 == 0) {
        return;
    }

    // auto group = [&](size_t idx) {
    //     idx += 1;
    //     std::vector<Block*> grp;
    //     while (idx < blocks.size()) {
    //         grp.push_back(blocks[idx - 1]);
    //         if (blocks[idx]->getBlockID() != BlockId::ANDTEXT) {
    //             break;
    //         }
    //         idx += 2;
    //     }
    //     return std::make_tuple(grp, idx);
    // };

    // auto[src, idx] = group(0);
    // auto[dst, end] = group(idx + 1);

    // auto add_prop = [&](Property prop) {
    //     for (Block* block : src) {
    //         block->addProperty(prop);
    //     }
    // };

    // std::optional<Property> prop = std::nullopt;
    // switch (blocks[idx + 1]->getBlockID()) {
    // case BlockId::YOUTEXT:
    //     prop = Property::YOU;
    //     break;
    // default:
    //     break;
    // }

    // if (!prop.has_value()) {
    //     return;
    // }

    // switch (blocks[idx]->getBlockID()) {
    // case BlockId::ISTEXT:
    //     blocks[0]->addProperty(Property::YOU);
    //     break;
    // default:
    //     break;
    // }
}
}

#endif