#include <gtest/gtest.h>

#include "sfml_texture_factory.mock.hpp"
#include "sfml_texture_loader.mock.hpp"

#include "sfml_texture_warehous.hpp"

using namespace ::testing;

namespace graphics
{
class sfml_texture_warehous_test : public Test
{
public:
    std::unique_ptr<mock_sfml_texture_factory> unique_factory{
        std::make_unique<StrictMock<mock_sfml_texture_factory>>()};
    mock_sfml_texture_factory* factory{unique_factory.get()};

    std::unique_ptr<mock_sfml_texture_loader> unique_loader{
        std::make_unique<StrictMock<mock_sfml_texture_loader>>()};
    mock_sfml_texture_loader* loader{unique_loader.get()};
};

TEST_F(sfml_texture_warehous_test, loadRealImageToTextureShouldNotThrow)
{
    // EXPECT_CALL(*factory, create()).WillOnce(Return(ByMove(nullptr)));//TODO:
    // should return mock texture

    // sfml_texture_warehous textures{std::move(unique_factory)};
    // ASSERT_THROW({textures.load("resources/bomb.png")}, );
}

TEST_F(sfml_texture_warehous_test, createOnlyOneTextureForEachImageFile)
{
    // sfml_texture_warehous textures{std::move(unique_factory)};
    // ASSERT_NO_THROW({
    //     auto& first_bomb = textures.load("resources/bomb.png");
    //     auto& second_bomb = textures.load("resources/bomb.png");

    //     EXPECT_EQ(&first_bomb, &second_bomb);
    // });
}

TEST_F(sfml_texture_warehous_test,
       eachTextureFromOtherImageFileShouldBeDifferent)
{
    // sfml_texture_warehous textures{std::move(unique_factory)};
    // ASSERT_NO_THROW({
    //     auto& bomb = textures.load("resources/bomb.png");
    //     auto& bomberman = textures.load("resources/bomberman.png");

    //     EXPECT_NE(&bomb, &bomberman);
    // });
}

TEST_F(sfml_texture_warehous_test, shouldThrowIfCanotCreateTexture)
{
    // sfml_texture_warehous textures{std::move(unique_factory)};

    // EXPECT_CALL(*factory, create()).WillOnce(Return(ByMove(nullptr)));
    // ASSERT_THROW(
    //     {
    //         try
    //         {
    //             textures.load("somepath.png");
    //         }
    //         catch (const texture_warehous::cannot_access& error)
    //         {
    //             EXPECT_STREQ("cannot load: somepath.png", error.what());
    //             throw;
    //         }
    //     },
    //     texture_warehous::cannot_access);
}

TEST_F(sfml_texture_warehous_test, shouldThrowIfloadInvalidImage)
{
    // sfml_texture_warehous textures{std::move(unique_factory)};
    // EXPECT_CALL(*factory, create()).WillOnce(Return(ByMove(nullptr))); //
    // TODO ASSERT_THROW(
    //     {
    //         try
    //         {
    //             textures.load("somepath.png");
    //         }
    //         catch (const texture_warehous::cannot_access& error)
    //         {
    //             EXPECT_STREQ("cannot load: somepath.png", error.what());
    //             throw;
    //         }
    //     },
    //     texture_warehous::cannot_access);
}
}
