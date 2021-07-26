#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <algorithm>
#include <vector>
#include <regex>
#include <unordered_map>

#include <element.h>
#include <utils.h>

class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  auto set(std::string_view text) -> void;
  auto parse() const -> std::vector<Element>;

private:
  std::string text;
  std::vector<std::string> lines;

  auto inline_scan(const std::string& line, ElemEnv env) const
      -> std::vector<Element>;
  auto line_scan() const -> std::vector<Element>;
};

#endif // PARSER_H
