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
    using PosVec = std::vector<std::tuple<size_t, size_t>>;

    // empty map validation
    MapWrapper<4, 3> empty_wrapper;
    REQUIRE(!empty_wrapper.move(std::make_tuple(1, 0), MoveType::RIGHT));

    // preparing test
    Map<4, 3> map;
    MapWrapper wrapper(&map);

    // movable entity validation
    // 1. entity nullity
    REQUIRE(!wrapper.move(std::make_tuple(1, 0), MoveType::RIGHT));

    Entity entity(BlockId::BABA, {}, "123456789");
    entity.addPosition(std::make_tuple(1, 0));
    map[0][1] = &entity;

    // 2. push validation
    REQUIRE(!wrapper.move(std::make_tuple(1, 0), MoveType::RIGHT));
    REQUIRE(map[0][1] == &entity);
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(1, 0) });

    entity.addProperty(Property::PUSH);
    REQUIRE(wrapper.move(std::make_tuple(1, 0), MoveType::RIGHT));
    REQUIRE(map[0][2] == &entity);
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(2, 0) });

    // 3. coordinate validation
    REQUIRE(!wrapper.move(std::make_tuple(2, 0), MoveType::UP));
    REQUIRE(map[0][2] == &entity);
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(2, 0) });

    // 4. stop validation
    Entity entity2(BlockId::FLAG, {}, "123456789");
    map[0][3] = &entity2;

    REQUIRE(wrapper.move(std::make_tuple(2, 0), MoveType::RIGHT));
    REQUIRE(map[0][3] == &entity);
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(3, 0) });

    entity2.addProperty(Property::STOP);
    entity2.addPosition(std::make_tuple(2, 0));
    map[0][2] = &entity2;

    REQUIRE(!wrapper.move(std::make_tuple(3, 0), MoveType::LEFT));
    REQUIRE(map[0][2] == &entity2);
    REQUIRE(entity2.getPosition() == PosVec{ std::make_tuple(2, 0) });
    REQUIRE(map[0][3] == &entity);
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(3, 0) });

    // adjacent entity validation
    entity2.addProperty(Property::PUSH);
    entity2.removeProperty(Property::STOP);

    REQUIRE(wrapper.move(std::make_tuple(3, 0), MoveType::LEFT));
    REQUIRE(map[0][2] == &entity);
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(2, 0) });
    REQUIRE(map[0][1] == &entity2);
    REQUIRE(entity2.getPosition() == PosVec{ std::make_tuple(1, 0) });
}

TEST_CASE("MapWrapper::updateBlocks", "[MapWrapper]")
{

}
