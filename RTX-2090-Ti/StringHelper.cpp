#include "pch.h"
#include "StringHelper.hpp"

#include <string>

namespace RTXLib::StringHelper {

std::string removeFileExtension(std::string filename) {
    int32_t i = static_cast<int32_t>(filename.size()) - 1;

    for (; i >= 0; i--) {
        if (filename[i] == '.') {
            if (i >= 1 &&
                filename[static_cast<std::string::size_type>(i) - 1] == '.')
                // something is wrong
                return filename;
            else
                break;
        }
    }

    if (i < 1) return filename;

    return filename.substr(0, i);
}

}  // namespace RTXLib::StringHelper
