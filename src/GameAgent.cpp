#include <vector>

#include "GameAgent.hpp"

bool GameAgent::checkWinCondition(std::vector<Entity::Position> you, std::vector<Entity::Position> win )
{
    for(auto y : you)
    {
        for(auto w : win)
        {
            if(std::get<0>(y) == std::get<0>(y) && std::get<1>(w) == std::get<1>(w))
            {
                return true;
            }
        }
    }
}