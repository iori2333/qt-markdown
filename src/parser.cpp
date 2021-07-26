#include <parser.h>
#include <iostream>

auto Parser::set(std::string_view text) -> void {
  this->text = text;
  this->lines = utils::split(text, "\n");
}

auto Parser::parse() const -> std::vector<Element> {
  auto line_elements = std::vector<std::vector<Element>>{};
  // Scan for each line and parse
  for (auto&& line : lines) {
    line_elements.push_back(inline_scan(line, ElemEnv::NORMAL));
  }
  return {};
}
