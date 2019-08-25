#include "Catch2/catch.hpp"

#include "Map.hpp"

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
    REQUIRE(fail(empty_wrapper.movable(std::make_tuple(0, 0, 0), MoveType::LEFT)));

    // preparing test
    Map<3, 4> map;
    MapWrapper wrapper(&map);

    // entity nullity validation
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0, 0), MoveType::RIGHT)));

    Entity entity(BlockId::BABA, {}, "123456789");
    map[0][1].push_back(&entity);

    // push validation
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0, 0), MoveType::RIGHT)));

    entity.addProperty(Property::PUSH);
    REQUIRE(wrapper.movable(std::make_tuple(1, 0, 0), MoveType::RIGHT)
        == std::make_tuple(true, 2, 0));

    // coordinate validation
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0, 0), MoveType::UP)));

    // stop validation
    Entity entity2(BlockId::FLAG, {}, "123456789");
    map[0][2].push_back(&entity2);

    REQUIRE(wrapper.movable(std::make_tuple(1, 0, 0), MoveType::RIGHT)
        == std::make_tuple(true, 2, 0));

    entity2.addProperty(Property::STOP);
    REQUIRE(fail(wrapper.movable(std::make_tuple(1, 0, 0), MoveType::RIGHT)));
}

TEST_CASE("MapWrapper::move", "[MapWrapper]")
{
    using BlockVec = std::vector<Block*>;
    using PosVec = std::vector<Entity::Position>;

    // empty map validation
    MapWrapper<4, 3> empty_wrapper;
    REQUIRE(!empty_wrapper.move(std::make_tuple(1, 0, 0), MoveType::RIGHT));

    // preparing test
    Map<4, 3> map;
    MapWrapper wrapper(&map);

    // movable entity validation
    // 1. entity nullity
    REQUIRE(!wrapper.move(std::make_tuple(1, 0, 0), MoveType::RIGHT));

    Entity entity(BlockId::BABA, {}, "123456789");
    entity.addPosition(std::make_tuple(1, 0, 0));
    map[0][1].push_back(&entity);

    // 2. push validation
    REQUIRE(!wrapper.move(std::make_tuple(1, 0, 0), MoveType::RIGHT));
    REQUIRE(map[0][1] == BlockVec{ &entity });
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(1, 0, 0) });

    entity.addProperty(Property::PUSH);
    REQUIRE(wrapper.move(std::make_tuple(1, 0, 0), MoveType::RIGHT));
    REQUIRE(map[0][2] == BlockVec{ &entity });
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(2, 0, 0) });

    // 3. coordinate validation
    REQUIRE(!wrapper.move(std::make_tuple(2, 0, 0), MoveType::UP));
    REQUIRE(map[0][2] == BlockVec{ &entity });
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(2, 0, 0) });

    // 4. stop validation
    Entity entity2(BlockId::FLAG, {}, "123456789");
    entity2.addPosition(std::make_tuple(3, 0, 0));
    map[0][3].push_back(&entity2);

    REQUIRE(wrapper.move(std::make_tuple(2, 0, 0), MoveType::RIGHT));
    REQUIRE(map[0][3] == BlockVec{ &entity2, &entity });
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(3, 0, 1) });

    Entity entity3(BlockId::BABA, { Property::STOP }, "1234566789");
    entity3.addPosition(std::make_tuple(2, 0, 0));
    map[0][2].push_back(&entity3);

    REQUIRE(!wrapper.move(std::make_tuple(3, 0, 1), MoveType::LEFT));
    REQUIRE(map[0][2] == BlockVec{ &entity3 });
    REQUIRE(entity3.getPosition() == PosVec{ std::make_tuple(2, 0, 0) });
    REQUIRE(map[0][3] == BlockVec{ &entity2, &entity });
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(3, 0, 1) });

    // adjacent entity validation
    entity3.addProperty(Property::PUSH);
    entity3.removeProperty(Property::STOP);

    REQUIRE(wrapper.move(std::make_tuple(3, 0, 1), MoveType::LEFT));
    REQUIRE(map[0][3] == BlockVec{ &entity2 });
    REQUIRE(entity2.getPosition() == PosVec{ std::make_tuple(3, 0, 0) });
    REQUIRE(map[0][2] == BlockVec{ &entity });
    REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(2, 0, 0) });
    REQUIRE(map[0][1] == BlockVec{ &entity3 });
    REQUIRE(entity3.getPosition() == PosVec{ std::make_tuple(1, 0, 0) });
}

TEST_CASE("MapWrapper::updateBlocks", "[MapWrapper]")
{
    using BlockVec = std::vector<Block*>;
    using PosVec = std::vector<std::tuple<size_t, size_t, size_t>>;

    // map nullity validation
    MapWrapper<4, 3> empty_wrapper;
    REQUIRE(!empty_wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    // preparing test
    Map<4, 3> map;
    MapWrapper wrapper(&map);

    const char* visual = "123456789";

    Entity baba_entity(BlockId::BABA, {}, visual);
    Text baba_text(BlockId::BABA, Property::ENTITY, {}, visual, &baba_entity);

    Entity flag_entity(BlockId::FLAG, {}, visual);
    Text flag_text(BlockId::FLAG, Property::ENTITY, {}, visual, &flag_entity);

    Text is_text(BlockId::IS, Property::INVALID, {}, visual);
    Text you_text(BlockId::YOU, Property::YOU, {}, visual);

    // `IS` text validation
    // 0. block nullity validation
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    // 1. coordinate validation
    map[0][2].push_back(&you_text);
    map[0][3].push_back(&you_text);
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(2, 0), MoveType::RIGHT, 3));

    // 2. no `IS` text
    map[0][1].push_back(&you_text);
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    // 3. first block `IS`
    map[0][1][0] = &is_text;
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    // 4. last block `IS`
    map[0][1][0] = &you_text;
    map[0][2][0] = &is_text;
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    // adjacenct text validation
    map[0][1][0] = &baba_entity;
    map[0][2][0] = &is_text;
    map[0][3][0] = &you_text;
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    map[0][3][0] = &flag_entity;
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    map[0][1][0] = &baba_text;
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    // left property
    map[0][1][0] = &you_text;
    map[0][3][0] = &baba_text;
    REQUIRE(!wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));

    // left entity, right property
    map[0][1][0] = &baba_text;
    map[0][3][0] = &you_text;
    REQUIRE(wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));
    REQUIRE(baba_entity.containProperty(Property::YOU));

    // left entity, right entity
    map[0][1][0] = &baba_text;
    map[0][3][0] = &flag_text;

    map[1][1].push_back(&baba_entity);
    map[1][3].push_back(&flag_entity);
    baba_entity.addPosition(std::make_tuple(1, 1, 0));
    flag_entity.addPosition(std::make_tuple(3, 1, 0));

    REQUIRE(wrapper.updateBlocks(std::make_tuple(1, 0), MoveType::RIGHT, 3));
    REQUIRE(baba_entity.getPosition() == PosVec{});
    REQUIRE(flag_entity.getPosition() == PosVec{ std::make_tuple(3, 1, 0), std::make_tuple(1, 1, 0) });
    REQUIRE(map[1][1] == BlockVec{ &flag_entity });
    REQUIRE(map[1][3] == BlockVec{ &flag_entity });
}
