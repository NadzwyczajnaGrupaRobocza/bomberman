#include <gtest/gtest.h>

#include "sfml_texture_loader.hpp"

namespace graphics
{
class sfml_texture_loader_test : public ::testing::Test
{
public:
};

TEST_F(sfml_texture_loader_test, loadRealImageToTextureShouldNotThrow)
{
    sfml_texture_loader textures;
    ASSERT_NO_THROW(textures.load("../data/bomb.png"));
}

TEST_F(sfml_texture_loader_test, createOnlyOneTextureForEachImageFile)
{
    sfml_texture_loader textures;
    ASSERT_NO_THROW({
        auto& first_bomb = textures.load("../data/bomb.png");
        auto& second_bomb = textures.load("../data/bomb.png");

        EXPECT_EQ(&first_bomb, &second_bomb);
    });
}


TEST_F(sfml_texture_loader_test, eachTextureFromOtherImageFileShouldBeDifferent)
{
    sfml_texture_loader textures;
    ASSERT_NO_THROW({
        auto& bomb = textures.load("../data/bomb.png");
        auto& bomberman = textures.load("../data/bomberman.png");

        EXPECT_NE(&bomb, &bomberman);
    });
}

TEST_F(sfml_texture_loader_test, loadInvalidImageToTextureShouldThrow)
{
    sfml_texture_loader textures;
    ASSERT_THROW(
        {
            try
            {
                textures.load("somepath.png");
            }
            catch (const texture_load_error& error)
            {
                EXPECT_STREQ("cannot load: somepath.png", error.what());
                throw;
            }
        },
        texture_load_error);
}
}
