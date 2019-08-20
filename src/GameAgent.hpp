#ifndef GAMEAGENT_HPP
#define GAMEAGENT_HPP

#include "Block.hpp"

class GameAgent
{
public:
    GameAgent() = default;
    ~GameAgent() = default;

    bool checkWinCondition(std::vector<Entity::Position>, std::vector<Entity::Position>);
    bool checkYouCondition(std::vector<Entity::Position>);

};
#endif