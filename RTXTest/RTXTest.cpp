#include "pch.h"
#include "CppUnitTest.h"

#include "GPUConfig.hpp"
#include "ImageHandler.hpp"
#include "StringHelper.hpp"

#include <string>
#include <utility>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTXTest {

// clang-format off
TEST_CLASS(GPUConfigTest) {
  public:
    TEST_METHOD(WarpPoints) {
        for (int i = 0; i < 1000; i++) {
            auto config = RTXLib::GPUConfig();
            config.output.dims = {69, 420};
            config.output.loops = 5;

            Assert::IsTrue(
                config.validateWarpLocations(), L"Warp points should be changed (grow)");
            Assert::AreEqual(5, static_cast<int32_t>(config.warpLocations.size()));

            for (const auto& [x, y] : config.warpLocations) {
                Assert::IsTrue(x >= 0, L"X is less than 0");
                Assert::IsTrue(y >= 0, L"Y is less than 0");
                Assert::IsTrue(x < 69, L"X exceeds the dimension");
                Assert::IsTrue(y < 420, L"Y exceeds the dimension");
            }

            config.output.loops = 3;
            Assert::IsTrue(
                config.validateWarpLocations(), L"Warp points should be changed (shrink)");
            Assert::AreEqual(3, (int)config.warpLocations.size());

            Assert::IsFalse(
                config.validateWarpLocations(), L"Warp points should remained the same");
        }
    }
};

TEST_CLASS(ImageHandler) {
  public:
    TEST_METHOD(ImageLoading) {
        auto handler = RTXLib::ImageHandler();
        Assert::IsFalse(handler.loadImage("/path/to/not/exist/file"));
    }
};

TEST_CLASS(StringHelper) {
  public:
    TEST_METHOD(removeFileExtension) {
        const auto testcases = std::vector<std::pair<std::string, std::string>>{
            {"bruh.jpeg", "bruh"},
            {"bruh.wtf", "bruh"},
            {"nevergonnagiveyouup", "nevergonnagiveyouup"},
            {"stack.overflow.jpeg.lol", "stack.overflow.jpeg"},
            {"illegalFileName.....", "illegalFileName...."},
            {"normalButWeird...wtf", "normalButWeird.."},
            {"", ""},
        };

        for(const auto& [test, expected] : testcases) {
            Assert::AreEqual(expected, RTXLib::StringHelper::removeFileExtension(test));
        }
    }
};

}  // namespace RTXTest
