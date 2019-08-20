#include <vector>

#include "GameAgent.hpp"

bool GameAgent::checkWinCondition(std::vector<Entity::Position> you, std::vector<Entity::Position> win )
{
    for(auto [you_x, you_y, you_z] : you)
    {
        for(auto [win_x, win_y, win_z] : win)
        {
            if(you_x == win_x && you_y == win_y)
            {
                return true;
            }
        }
    }
    return false;
}

bool GameAgent::checkYouCondition(std::vector<Entity::Position> you)
{
    return you.empty();
}