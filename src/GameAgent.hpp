#ifndef GAMEAGENT_HPP
#define GAMEAGENT_HPP

#include "Block.hpp"
#include "Map.hpp"

class GameAgent
{
public:
    GameAgent() = default;
    ~GameAgent() = default;

    bool checkWinCondition(const std::vector<Entity::Position>& you, const std::vector<Entity::Position>& win);
    bool checkRemainYou(const std::vector<Entity::Position>& you);
};
#endif