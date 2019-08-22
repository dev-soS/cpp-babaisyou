#ifndef GAMEAGENT_HPP
#define GAMEAGENT_HPP

#include "Block.hpp"
#include "IOInterface.hpp"
#include "Map.hpp"

class GameAgent
{
public:
    GameAgent(IOInterface* io);
    ~GameAgent() = default;

    template <size_t Width, size_t Height>
    void Run(const Map<Width, Height>& map);

    bool checkWinCondition(const std::vector<Entity::Position>& you, const std::vector<Entity::Position>& win);
    bool checkRemainYou(const std::vector<Entity::Position>& you);

private:
    IOInterface* io;

    template <size_t Width, size_t Height>
    Map<Width, Height> CopyMap();
};
#endif