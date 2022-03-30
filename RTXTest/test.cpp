#include "pch.h"
#include "GPUConfig.hpp"
#include "ImageHandler.hpp"

namespace RTXTest {

TEST(GPUConfigTest, WarpPoints) {
    auto config = RTXLib::GPUConfig();
    config.output.dims = {69, 420};
    config.output.loops = 5;

    ASSERT_TRUE(config.validateWarpLocations());
    ASSERT_EQ(5, config.warpLocations.size());

    for (const auto& [x, y] : config.warpLocations) {
        ASSERT_GE(x, 0);
        ASSERT_GE(y, 0);
        ASSERT_LT(x, 69);
        ASSERT_LT(y, 420);
    }

    config.output.loops = 3;
    ASSERT_TRUE(config.validateWarpLocations());
    ASSERT_EQ(3, config.warpLocations.size());

    ASSERT_FALSE(config.validateWarpLocations());
}

TEST(ImageHandler, ImageHandler) {
    auto handler = RTXLib::ImageHandler();
    ASSERT_FALSE(handler.loadImage("/path/to/not/exist/file"));
}

}  // namespace RTXTest
