#include <regex>
#include <unordered_map>

#include <parser.h>

auto inline_regs = std::vector<std::pair<std::regex, ElemType>>{
    {std::regex(R"(\*\*(.*?)\*\*)"), ElemType::BOLD},
    {std::regex(R"(\*([^.*]{1,}?)\*)"), ElemType::ITALIC},
    {std::regex(R"(`(.*?)`)"), ElemType::REFER_INLINE},
    {std::regex(R"(\$([^\$]{1,}?)\$)"), ElemType::MATH_INLINE},
    {std::regex(R"(\$\$(.*?)\$\$)"), ElemType::MATH},
    {std::regex(R"(!(\[.*?\]\(.*?\)))"), ElemType::PICTURE},
    {std::regex(R"((\[.*?\]\(.*?\)))"), ElemType::LINK},
    {std::regex(R"((#+ +))"), ElemType::NORMAL},
    {std::regex(R"((> +))"), ElemType::NORMAL},
};

auto Parser::inline_scan(const std::string& line, ElemEnv env) const
    -> std::vector<Element> {
  auto i = 0, n = static_cast<int>(line.size());
  auto res = std::vector<Element>{};
  auto tmp = std::string{}; // for regular texts

  while (i < n) {
    auto flag = false;

    for (auto&& [reg, type] : inline_regs) {
      std::smatch match;
      if (std::regex_search(line.begin() + i, line.end(), match, reg,
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
      tmp.push_back(line[i]);
      i++;
    }
  }

  if (!tmp.empty()) {
    res.push_back(Element{tmp, env, ElemType::NORMAL});
  }
  return res;
}
