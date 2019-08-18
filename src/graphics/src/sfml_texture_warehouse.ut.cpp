#include <gtest/gtest.h>

#include "sfml_texture_loader.mock.hpp"

#include "sfml_texture_warehouse.hpp"

using namespace ::testing;

namespace graphics
{
class sfml_texture_warehouse_test : public Test
{
protected:
    void SetUp() override
    {
        ON_CALL(*loader, load(_, _)).WillByDefault(Return(success));
    }

    const texture_path bomb_path{"destination/bomb.png"};
    const texture_path ghost_path{"destination/ghost.png"};
    const bool success{true};
    const bool fail{false};

    std::unique_ptr<mock_sfml_texture_loader> unique_loader{
        std::make_unique<NiceMock<mock_sfml_texture_loader>>()};
    mock_sfml_texture_loader* loader{unique_loader.get()};

    sfml_texture_warehouse texture_keeper{std::move(unique_loader)};
};

ACTION_P(SavePointerFirstArg, pointer)
{
    *pointer = &arg0;
}

TEST_F(sfml_texture_warehouse_test, getAccesByFirstTyimeShouldAllocateTexture)
{
    sf::Texture* loaded_texture{nullptr};
    EXPECT_CALL(*loader, load(_, bomb_path))
        .WillOnce(DoAll(SavePointerFirstArg(&loaded_texture), Return(success)));

    auto& bomb_tx = texture_keeper.get_access(bomb_path);

    ASSERT_TRUE(loaded_texture);
    EXPECT_EQ(loaded_texture, &bomb_tx);
}

TEST_F(sfml_texture_warehouse_test,
       getAccesSecondTimeShouldNotAllocateButReturnSameTexture)
{
    auto& first_bomb_tx = texture_keeper.get_access(bomb_path);

    EXPECT_CALL(*loader, load(_, _)).Times(0);

    auto& second_bomb_tx = texture_keeper.get_access(bomb_path);

    EXPECT_EQ(&first_bomb_tx, &second_bomb_tx);
}

TEST_F(sfml_texture_warehouse_test,
       getAccesSecondTimeButWithNewFileShouldAllocateNewTexture)
{
    auto& bomb_tx = texture_keeper.get_access(bomb_path);

    EXPECT_CALL(*loader, load(_, ghost_path)).WillOnce(Return(success));

    auto& ghost_tx = texture_keeper.get_access(ghost_path);

    EXPECT_NE(&bomb_tx, &ghost_tx);
}

TEST_F(sfml_texture_warehouse_test, ifTextureNotLoadedProperlyItShouldThrow)
{
    EXPECT_CALL(*loader, load(_, bomb_path)).WillOnce(Return(fail));

    ASSERT_THROW(
        {
            try
            {
                texture_keeper.get_access(bomb_path);
            }
            catch (const std::exception& ex)
            {
                EXPECT_STREQ("cannot load: destination/bomb.png", ex.what());
                throw;
            }
        },
        texture_warehouse::cannot_access);
}
}
