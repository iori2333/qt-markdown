#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>
#include <element.h>

auto operator<<(std::ostream& os, const ElemType type) -> std::ostream&;

auto operator<<(std::ostream& os, const ElemEnv env) -> std::ostream&;

auto split(std::string_view s, std::string_view delims = "\n")
    -> std::vector<std::string>;

#endif // UTILS_H
