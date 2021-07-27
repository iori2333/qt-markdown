#include <parser.h>
#include <iostream>

using ElemLines = std::vector<std::vector<Element>>;

auto Parser::set(std::string_view text) -> void {
  this->text = text;
  this->lines = utils::split(text, "\n");
}

auto Parser::parse() const -> ElemLines {
  auto line_elements = ElemLines{};
  auto cross_line = ElemEnv::NORMAL;

  // scan every line and parse
  for (auto&& line : lines) {
    auto env = line_scan(line);
    if (env == ElemEnv::CODE || env == ElemEnv::REFER_CROSS) {
      if (env == cross_line) {
        cross_line = ElemEnv::NORMAL;
      } else {
        cross_line = env;
      }
      continue;
    }

    if (cross_line != ElemEnv::NORMAL) {
      line_elements.push_back({Element{line, cross_line, ElemType::NORMAL}});
    } else {
      line_elements.push_back(inline_scan(line, env));
    }
  }
  return line_elements;
}
