#include <parser.h>

auto line_regs = std::vector<std::pair<std::regex, ElemEnv>>{
    {std::regex(R"(#+ +.+)"), ElemEnv::TITLE},
    {std::regex(R"( *\d+\. +.+)"), ElemEnv::OLIST},
    {std::regex(R"( *[+|-] +.+)"), ElemEnv::ULIST},
    {std::regex(R"(```.*)"), ElemEnv::CODE},
    {std::regex(R"(> .+)"), ElemEnv::REFER},
    {std::regex(R"(>>>.*)"), ElemEnv::REFER_CROSS},
};

/**
 * @brief Parser::line_scan parses line env and return its type
 * @param line the line to be parsed
 * @return the env to which the line belongs
 */
auto Parser::line_scan(const std::string& line) const -> ElemEnv {
  for (auto&& [reg, type] : line_regs) {
    if (std::regex_match(line, reg)) {
      return type;
    }
  }
  return ElemEnv::NORMAL;
}
