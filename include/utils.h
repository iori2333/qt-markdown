#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <element.h>

auto split(std::string_view s, std::string_view delims = "\n")
    -> std::vector<std::string>;

auto replace_string(std::string& s, std::string_view from, std::string_view to)
    -> void;

#endif // UTILS_H
