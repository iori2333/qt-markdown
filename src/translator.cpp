#include <iostream>
#include <fstream>
#include <format>
#include <unordered_map>
#include <regex>

#include <translator.h>
#include <utils.h>

using ElemLine = std::vector<Element>;
using ElemLines = std::vector<ElemLine>;
using EscapePair = std::pair<std::string_view, std::string_view>;

auto inline_tags = std::unordered_map<ElemType, std::string_view>{
    {ElemType::BOLD, "<span class=\"bold-text\">{}</span>"},
    {ElemType::ITALIC, "<span class=\"italic-text\">{}</span>"},
    {ElemType::REFER_INLINE, "<span class=\"refer-text\">{}</span>"},
    {ElemType::MATH_INLINE, "<span class=\"italic-text\">{}</span>"},
    {ElemType::MATH, "<span class=\"italic-text\">{}</span>"},
    {ElemType::LINK, "<a href=\"{}\">{}</a>"},
    {ElemType::PICTURE, "<img src=\"{}\", alt=\"{}\">"},
    {ElemType::NORMAL, "{}"},
};

auto env_tags = std::unordered_map<ElemEnv, std::string_view>{
    {ElemEnv::NORMAL, "<div class=\"normal-text\">{}</div>"},
    {ElemEnv::CODE, "<div class=\"code-block\">{}</div>"},
    {ElemEnv::OLIST, "<div class=\"list-item\">{}</div>"},
    {ElemEnv::ULIST, "<div class=\"list-item\">{}</div>"},
    {ElemEnv::REFER, "<div class=\"refer-block\">{}</div>"},
    {ElemEnv::REFER_CROSS, "<div class=\"refer-block\">{}</div>"},
    {ElemEnv::TITLE, "<h{0}>{1}</h{0}>"},
};

auto escapes = std::vector<EscapePair>{
    {"&", "&amp;"},
    {"<", "&lt;"},
    {">", "&gt;"},
};

auto pic_reg = std::regex(R"(!\[(.*?)\]\((.*?)\))");
auto link_reg = std::regex(R"(\[(.*?)\]\((.*?)\))");

static auto escape(const std::string& s) -> std::string {
  auto res = std::string(s);
  for (auto&& [from, to] : escapes) {
    replace_string(res, from, to);
  }
  return res;
}

auto Translator::translate_element(const Element& element) const
    -> std::string {
  auto content = escape(element.content);
  switch (element.type) {
  case ElemType::NORMAL:
    return content;
    break;
  case ElemType::PICTURE: {
    auto match = std::smatch{};
    std::regex_match(content, match, pic_reg);
    return std::format(inline_tags[ElemType::PICTURE], match[1].str(),
                       match[2].str());
    break;
  }
  case ElemType::LINK: {
    auto match = std::smatch{};
    std::regex_match(content, match, link_reg);
    return std::format(inline_tags[ElemType::LINK], match[2].str(),
                       match[1].str());
    break;
  }
  default:
    return std::format(inline_tags[element.type], content);
  }
  throw std::runtime_error("shouldn't reach here");
}

auto Translator::translate_line(const ElemLine& line, bool ignore_first) const
    -> std::string {
  auto ret = std::string{};
  for (auto&& element : line) {
    if (ignore_first) {
      ignore_first = false;
      continue;
    }
    ret += translate_element(element);
  }

  return ret;
}

auto Translator::translate(const ElemLines& lines) -> std::string {
  auto length = lines.size();
  auto res = std::string{};

  for (auto i = 0; i < length; i++) {
    auto env = lines[i][0].env;

    switch (env) {
    case ElemEnv::TITLE: {
      auto rank = std::count(lines[i][0].content.begin(),
                             lines[i][0].content.end(), '#');
      auto parsed_line = translate_line(lines[i], true);
      res += std::format(env_tags[ElemEnv::TITLE], rank, parsed_line);
      break;
    }
    case ElemEnv::REFER: {
      auto parsed_line = translate_line(lines[i], true);
      res += std::format(env_tags[ElemEnv::REFER], parsed_line);
      break;
    }
    case ElemEnv::CODE:
    case ElemEnv::OLIST:
    case ElemEnv::ULIST:
    case ElemEnv::REFER_CROSS: {
      auto tmp = std::string{};
      while (i < length && lines[i][0].env == env) {
        tmp += translate_line(lines[i]) + "<br/>\n";
        i++;
      }
      res += std::format(env_tags[env], tmp);
      i--;
      break;
    }
    default:
      res += std::format(env_tags[env], translate_line(lines[i])) + "<br/>\n";
    }
  }
  last_result = res;
  return res;
}

auto Translator::save(const std::string& path) const -> bool {
  auto os = std::ofstream(path, std::ofstream::in);
  try {
    if (!last_result.empty()) {
      os << last_result;
      return true;
    }
  } catch (std::exception e) {
    std::cerr << e.what();
  }

  return false;
}
