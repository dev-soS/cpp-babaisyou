#ifndef MAP_WRAPPER_HPP
#define MAP_WRAPPER_HPP

#include <map>
#include <tuple>

#include "Block.hpp"
#include "Enums.hpp"
#include "Map.hpp"

template <size_t Width, size_t Height>
class MapWrapper {
public:
    MapWrapper(Map<Width, Height>* map = nullptr) : map(map)
    {
        // Do nothing
    }

    static std::tuple<bool, size_t, size_t> next(std::tuple<size_t, size_t> pos, MoveType direction) {
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

    std::tuple<bool, size_t, size_t> movable(std::tuple<size_t, size_t> pos, MoveType direction) const
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

    bool move(std::tuple<size_t, size_t> pos, MoveType direction)
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

    void update_blocks(std::tuple<size_t, size_t> pos, MoveType direction, size_t cnt)
    {
        auto text_is = [](Block* block) {
            return block->getBlockId() != BlockId::IS && block->getBlockType() != BlockType::TEXT;
        };

        auto[x, y] = pos;
        

        if (auto iter = std::find_if(blocks.begin(), blocks.end(), is_finder);
            iter != blocks.end())
        {
            if (iter != blocks.begin() && iter + 1 != blocks.end())
            {
                Block* src = *(iter - 1);
                Block* dst = *(iter + 1);

                if (src->getBlockType() == BlockType::TEXT && dst->getBlockType() == BlockType::TEXT)
                {
                    Text* src_text = dynamic_cast<Text*>(src);
                    Text* dst_text = dynamic_cast<Text*>(dst);


                }
            }
        }
    }

private:
    Map<Width, Height>* map;
};

#endif