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
    auto fail = [](auto tup) { return !std::get<0>(tup); };

    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(0, 0), MoveType::RIGHT)
        == std::make_tuple(true, 1, 0));
    REQUIRE(fail(MapWrapper<3, 4>::next(std::make_tuple(0, 0), MoveType::LEFT)));

    REQUIRE(fail(MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::RIGHT)));
    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::LEFT)
        == std::make_tuple(true, 1, 0));
    
    REQUIRE(fail(MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::UP)));
    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(2, 0), MoveType::DOWN)
        == std::make_tuple(true, 2, 1));
    
    REQUIRE(MapWrapper<3, 4>::next(std::make_tuple(2, 3), MoveType::UP)
        == std::make_tuple(true, 2, 2));
    REQUIRE(fail(MapWrapper<3, 4>::next(std::make_tuple(2, 3), MoveType::DOWN)));
}

TEST_CASE("MapWrapper::movable", "[MapWrapper]")
{
    auto fail = [](auto tup) { return !std::get<0>(tup); };

    // empty map validation
    MapWrapper<3, 4> empty_wrapper;
    REQUIRE(fail(empty_wrapper.movable(std::make_tuple(0, 0), MoveType::LEFT)));

    // preparing test
    Map<3, 4> map;
    MapWrapper wrapper(&map);

    // entity nullity validation
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0), MoveType::RIGHT)));

    Entity entity(BlockId::BABA, {}, "123456789");
    map[0][1] = &entity;

    // push validation
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0), MoveType::RIGHT)));

    entity.addProperty(Property::PUSH);
    REQUIRE(wrapper.movable(std::make_tuple(1, 0), MoveType::RIGHT)
        == std::make_tuple(true, 2, 0));

    // coordinate validation
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0), MoveType::UP)));

    // stop validation
    Entity entity2(BlockId::FLAG, {}, "123456789");
    map[0][2] = &entity2;

    REQUIRE(wrapper.movable(std::make_tuple(1, 0), MoveType::RIGHT)
        == std::make_tuple(true, 2, 0));

    entity2.addProperty(Property::STOP);
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0), MoveType::RIGHT)));
}

TEST_CASE("MapWrapper::move", "[MapWrapper]")
{

}

TEST_CASE("MapWrapper::updateBlocks", "[MapWrapper]")
{

}
