#include "parser.h"
#include <iostream>

Parser::Parser() {}

std::unordered_map<ElemType, std::regex> Parser::type_regs{
    {ElemType::NORMAL, std::regex(R"(.*?)")},
};

auto inline_regs = std::vector<std::pair<std::regex, ElemType>>{
    {std::regex(R"(\*\*(.*?)\*\*)"), ElemType::BOLD},
    {std::regex(R"(\*([^.*]{1,}?)\*)"), ElemType::ITALIC},
    {std::regex(R"(`(.*?)`)"), ElemType::REFER_INLINE},
    {std::regex(R"(\$([^\$]{1,}?)\$)"), ElemType::MATH_INLINE},
    {std::regex(R"(\$\$(.*?)\$\$)"), ElemType::MATH},
    {std::regex(R"(!(\[.*?\]\(.*?\)))"), ElemType::PICTURE},
    {std::regex(R"((\[.*?\]\(.*?\)))"), ElemType::LINK},
};

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

/**
 * @brief Parser::first_scan scans for inline tokens and convert to a list of
 * elements
 * @param line the line to be processed
 * @return list of tokens
 */
auto Parser::inline_scan(std::string_view line, ElemEnv env) const
    -> std::vector<Element> {
  auto i = 0, n = static_cast<int>(line.size());
  auto res = std::vector<Element>{};
  const auto s = std::string(line); // regex_match does not support string_view
  auto tmp = std::string{};         // for regular texts

  while (i < n) {
    auto flag = false;

    for (auto&& [reg, type] : inline_regs) {
      std::smatch match;
      if (std::regex_search(s.begin() + i, s.end(), match, reg,
                            std::regex_constants::match_continuous)) {
        flag = true;
        if (!tmp.empty()) {
          res.push_back(Element{tmp, env, ElemType::NORMAL});
          tmp.clear();
        }
        i += static_cast<int>(match[0].length());
        res.push_back(Element{match[1].str(), env, type});
        break;
      }
    }

    if (!flag) {
      tmp.push_back(s[i]);
      i++;
    }
  }

  if (!tmp.empty()) {
    res.push_back(Element{tmp, ElemEnv::NORMAL, ElemType::NORMAL});
  }
  return res;
}
