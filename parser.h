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
  Parser();
  auto set(std::string_view text) -> void;
  auto parse() const -> std::vector<Element>;

private:
  static std::unordered_map<ElemType, std::regex> type_regs;
  static std::unordered_map<ElemEnv, std::regex> env_regs;

  std::string text;
  std::vector<std::string_view> lines;

  auto inline_scan(std::string_view line, ElemEnv env) const
      -> std::vector<Element>;
  auto line_scan() const -> std::vector<Element>;
};

#endif // PARSER_H
