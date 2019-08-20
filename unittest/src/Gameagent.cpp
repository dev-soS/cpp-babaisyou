#include "Catch2/catch.hpp"

#include "GameAgent.hpp"

TEST_CASE("GameAgent::checkWinCondition","[GameAgent]")
{
    GameAgent gameagent;
    Entity you(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");
    Entity win(BlockId::FLAG, { Property::PUSH , Property::WIN}, "         ");

    you.addPosition(std::make_tuple(0,0,0));
    you.addPosition(std::make_tuple(1,2,3));
    you.addPosition(std::make_tuple(3,6,9));

    win.addPosition(std::make_tuple(1,3,3));
    REQUIRE(!gameagent.checkWinCondition(you.getPosition(),win.getPosition()));

    win.addPosition(std::make_tuple(5,6,7));
    win.addPosition(std::make_tuple(3,6,6));
    REQUIRE(gameagent.checkWinCondition(you.getPosition(),win.getPosition()));
}

TEST_CASE("GameAgent::checkYouCondition","[GameAgent]")
{
    GameAgent gameagent;
    Entity you(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");

    REQUIRE(gameagent.checkYouCondition(you.getPosition()));

    you.addPosition(std::make_tuple(0,0,0));
    REQUIRE(!gameagent.checkYouCondition(you.getPosition()));

    you.modifyPosition(std::make_tuple(0,0,0),std::make_tuple(1,2,3));
    REQUIRE(!gameagent.checkYouCondition(you.getPosition()));

    you.resetPosition();
    REQUIRE(gameagent.checkYouCondition(you.getPosition()));
}
