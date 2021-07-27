#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <algorithm>
#include <regex>
#include <unordered_map>

#include <interface.h>
#include <utils.h>

class Parser : public IParser {
public:
  Parser() = default;
  ~Parser() = default;

  auto set(std::string_view text) -> void override;
  auto parse() const -> std::vector<std::vector<Element>> override;

private:
  std::string text;
  std::vector<std::string> lines;

  auto line_scan(const std::string& line) const -> ElemEnv;
  auto inline_scan(const std::string& line, ElemEnv env) const
      -> std::vector<Element>;
};

#endif // PARSER_H
