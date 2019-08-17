#include "Catch2/catch.hpp"

#include "Map.hpp"
#include "MapWrapper.hpp"

TEST_CASE("MapWrapper::Constructor", "[MapWrapper]")
{
    MapWrapper<3, 3> empty_wrapper;
    REQUIRE(true);

    Map<3, 3> map;
    MapWrapper<3, 3> wrapper(&map);
    REQUIRE(true);
}

TEST_CASE("MapWrapper::next", "[MapWrapper]")
{
    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(0, 0), MoveType::RIGHT)
        == std::make_tuple(true, 1, 0));
    auto[fail, x, y] = MapWrapper<3, 4>::next(std::make_tuple(0, 0), MoveType::LEFT);
    REQUIRE(!fail);

    auto[fail1, x1, y1] = MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::RIGHT);
    REQUIRE(!fail1);
    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::LEFT)
        == std::make_tuple(true, 1, 0));
    
    auto[fail2, x2, y2] = MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::UP);
    REQUIRE(!fail2);
    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::DOWN)
        == std::make_tuple(true, 2, 1));
    
    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(2, 3), MoveType::UP)
        == std::make_tuple(true, 2, 2));
    auto[fail3, x3, y3] = MapWrapper<3, 4>::next(std::make_tuple(2, 3), MoveType::DOWN);
    REQUIRE(!fail3);
}