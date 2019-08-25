#ifndef MAP_WRAPPER_HPP
#define MAP_WRAPPER_HPP

#include <map>
#include <optional>
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

    static std::tuple<bool, size_t, size_t> next(std::tuple<size_t, size_t> pos, MoveType direction)
    {
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

    std::tuple<bool, size_t, size_t> movable(std::tuple<size_t, size_t, size_t> pos, MoveType direction) const
    {
        // member nullity check
        if (map == nullptr)
        {
            return std::make_tuple(false, 0, 0);
        }

        Map<Width, Height>& map_ref = *map;

        // if current entity has push property
        auto[x, y, z] = pos;
        const std::vector<Block*>& current = map_ref[y][x];
        // TODO: Add property not only push, but also move etc.
        if (current.size() <= z || !current[z]->containProperty(Property::PUSH))
        {
            return std::make_tuple(false, 0, 0);
        }

        // next coordinate validation
        auto[possible, new_x, new_y] = next(std::make_tuple(x, y), direction);
        if (!possible) 
        {
            return std::make_tuple(false, 0, 0);
        }

        // stop validation
        const std::vector<Block*>& block = map_ref[new_y][new_x];
        for (const Block* block : map_ref[new_y][new_x])
        {
            if (block->containProperty(Property::STOP))
            {
                return std::make_tuple(false, 0, 0);
            }
        }

        return std::make_tuple(true, new_x, new_y);
    }

    bool move(std::tuple<size_t, size_t, size_t> pos, MoveType direction)
    {
        // member nullity check
        if (map == nullptr)
        {
            return false;
        }

        Map<Width, Height>& map_ref = *map;

        // if entity is movable
        auto[x, y, z] = pos;
        auto[possible, new_x, new_y] = movable(pos, direction);
        if (possible)
        {
            // push validation
            int new_z = 0;
            for (const Block* block : map_ref[new_y][new_x])
            {
                if (block->containProperty(Property::PUSH))
                {
                    break;
                }
                ++new_z;
            }

            // if push property exist in some blocks
            if (new_z < map_ref[new_y][new_x].size())
            {
                move(std::make_tuple(new_x, new_y, new_z), direction);
            }

            // move block
            Block* block = map_ref[y][x][z];
            map_ref[new_y][new_x].push_back(block);
            map_ref[y][x].erase(map_ref[y][x].begin() + z);

            if (block->getBlockType() == BlockType::ENTITY) {
                // modify position
                Entity* entity = dynamic_cast<Entity*>(block);
                size_t z_axis = map_ref[new_y][new_x].size() - 1;
                entity->modifyPosition(pos, std::make_tuple(new_x, new_y, z_axis));
            }
            return true;
        }
        return false;
    }

    bool updateBlocks(std::tuple<size_t, size_t> pos, MoveType direction, size_t cnt)
    {
        // member nullity check
        if (map == nullptr)
        {
            return false;
        }

        Map<Width, Height>& map_ref = *map;

        auto text_is = [](Block* block) {
            return block != nullptr
                && block->getBlockId() == BlockId::IS
                && block->getBlockType() == BlockType::TEXT;
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

            size_t find_z = 0;
            for (Block* block : map_ref[next_y][next_x])
            {
                if (text_is(block))
                {
                    find = true;
                    break;
                }
                ++find_z;
            }

            if (find_z < map_ref[next_y][next_x].size())
            {
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
            auto text_finder = [](std::vector<Block*>& vec) -> Block* {
                for (Block* block : vec)
                {
                    if (block->getBlockType() == BlockType::TEXT)
                    {
                        return block;
                    }
                }
                return nullptr;
            };

            Block* dst = text_finder(map_ref[prev_y][prev_x]);
            Block* src = text_finder(map_ref[next_y][next_x]);

            // if adjacent block is text type
            if (src != nullptr && dst != nullptr)
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
                        for (auto const& entity_pos : dst_entity->getPosition())
                        {
                            auto[x, y, z] = entity_pos;
                            map_ref[y][x][z] = src_entity;
                            src_entity->addPosition(entity_pos);
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