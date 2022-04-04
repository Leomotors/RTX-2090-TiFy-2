#include "pch.h"
#include "StringHelper.hpp"

#include <string>

namespace RTXLib::StringHelper {

std::string removeFileExtension(std::string filename) {
    auto i = filename.size() - 1;

    if (filename[i] == '.') return filename;

    for (; i >= 0; i--) {
        if (filename[i] == '.' && (i <= 0 || filename[i - 1] != '.')) {
            break;
        }
    }

    if (i < 1) return filename;

    return filename.substr(0, i);
}

}  // namespace RTXLib::StringHelper
