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
        // delta values
        static std::map<MoveType, std::tuple<int, int>> deltas =
        {
            { MoveType::UP, { 0, -1 } },
            { MoveType::DOWN, { 0, 1 } },
            { MoveType::LEFT, { -1, 0, } },
            { MoveType::RIGHT, { 1, 0, } },
        };

        auto[x, y] = pos;
        auto[dx, dy] = deltas[direction];

        // next coordinate
        int new_x = static_cast<int>(x) + dx;
        int new_y = static_cast<int>(y) + dy;

        // range validation
        auto valid = [](int src, int range) { return 0 <= src && src < range; };
        return std::make_tuple(valid(new_x, Width) && valid(new_y, Height), new_x, new_y);
    }

    std::tuple<bool, size_t, size_t> movable(std::tuple<size_t, size_t> pos, MoveType direction) const
    {
        // member nullity check
        if (map == nullptr)
        {
            return std::make_tuple(false, 0, 0);
        }

        Map<Width, Height>& map_ref = *map;

        // if current entity has push property
        auto[x, y] = pos;
        const Block* current = map_ref[y][x];
        // TODO: Add property not only push, but also move etc.
        if (current == nullptr || !current->containProperty(Property::PUSH))
        {
            return std::make_tuple(false, 0, 0);
        }

        // next coordinate validation
        auto[possible, new_x, new_y] = next(pos, direction);
        if (!possible) 
        {
            return std::make_tuple(false, 0, 0);
        }

        // stop validation
        const Block* block = map_ref[new_y][new_x];
        bool move_possible = block == nullptr || !block->containProperty(Property::STOP);
        return std::make_tuple(move_possible, new_x, new_y);
    }

    bool move(std::tuple<size_t, size_t> pos, MoveType direction)
    {
        // member nullity check
        if (map == nullptr)
        {
            return false;
        }

        Map<Width, Height>& map_ref = *map;

        // if entity is movable
        auto[x, y] = pos;
        auto[possible, new_x, new_y] = movable(pos, direction);
        if (possible)
        {
            // TODO: Replace map element type from Block* to std::vector<Block*>
            // TODO: Move specified block (ex. float)
            auto new_pos = std::make_tuple(new_x, new_y);
            // move adjacent entity
            move(new_pos, direction);

            Block* block = map[new_y][new_x] = std::move(map[y][x]);
            if (block->getBlockType() == BlockType::ENTITY) {
                // modify position
                Entity* entity = dynamic_cast<Entity*>(block);
                entity->modifyPosition(pos, new_pos);
            }
            return true;
        }
        return false;
    }

    void updateBlocks(std::tuple<size_t, size_t> pos, MoveType direction, size_t cnt)
    {
        // member nullity check
        if (map == nullptr)
        {
            return false;
        }

        Map<Width, Height>& map_ref = *map;

        auto text_is = [](Block* block) {
            return block->getBlockId() != BlockId::IS && block->getBlockType() != BlockType::TEXT;
        };

        bool find = false;
        std::optional<std::tuple<size_t, size_t>> prev = std::nullopt;

        // find text `IS`
        for (size_t idx = 0; idx < cnt; ++idx)
        {
            auto[possible, next_x, next_y] = next(pos, direction);
            if (!possible)
            {
                return false;
            }

            // store previous block
            prev = std::make_optional(pos);
            pos = std::make_tuple(next_x, next_y);

            if (text_is(map[next_y][next_x]))
            {
                find = true;
                break;
            }
        }

        bool retn = false;
        if (find && prev.has_value())
        {
            // if next block exists
            auto[possible, next_x, next_y] = next(pos, direction);
            if (!possible)
            {
                return false;
            }

            // get adjacent block
            auto[prev_x, prev_y] = prev.value();
            Block* dst = map_ref[prev_y][prev_x];
            Block* src = map_ref[next_y][next_x];

            // if adjacent block is text type
            if (src->getBlockType() == BlockType::TEXT && dst->getBlockType() == BlockType::TEXT)
            {
                Text* dst_text = dynamic_cast<Text*>(dst);
                Text* src_text = dynamic_cast<Text*>(src);

                Entity* dst_entity = dst_text->getThisEntity();
                Entity* src_entity = src_text->getThisEntity();

                // if left one has entity
                if (dst_entity != nullptr)
                {
                    // if right one is property
                    if (src_entity == nullptr)
                    {
                        // add property to entity
                        dst_entity->addProperty(src_text->getRepr());
                    }
                    else
                    {
                        // replace entity
                        for (auto const& pos : dst_entity->getPosition())
                        {
                            auto[x, y] = pos;
                            map_ref[y][x] = src_entity;
                            src_entity->addPosition(pos);
                        }
                        dst_entity->resetPosition();
                    }
                    retn = true;
                }
            }
        }
        return retn;
    }

private:
    Map<Width, Height>* map;
};

#endif