#include <parser.h>
#include <iostream>

auto Parser::set(std::string_view text) -> void {
  this->text = text;
  this->lines = utils::split(text, "\n");
}

auto Parser::parse() const -> std::vector<Element> {
  auto line_elements = std::vector<std::vector<Element>>{};
  // scan every line and parse
  for (auto&& line : lines) {
    auto env = line_scan(line);
    line_elements.push_back(inline_scan(line, env));
  }
  return {};
}
