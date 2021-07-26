#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace utils {
auto split(std::string_view s, std::string_view delims = "\n")
    -> std::vector<std::string>;
} // namespace utils

#endif // UTILS_H
