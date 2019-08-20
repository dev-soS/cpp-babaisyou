#ifndef GAMEAGENT_HPP
#define GAMEAGENT_HPP



#include "Block.hpp"

class GameAgent
{
public:
    GameAgent();
    ~GameAgent();

    bool GameAgent::checkWinCondition(std::vector<Entity::Position>, std::vector<Entity::Position>);

    
};
#endif