#include <utils.h>

auto split(std::string_view s, std::string_view delims)
    -> std::vector<std::string> {
  auto out = std::vector<std::string>{};
  auto pos = 0llu;

  while (pos < s.size()) {
    auto next = s.find_first_of(delims, pos);
    if (next != pos) {
      out.emplace_back(s.substr(pos, next - pos));
    }

    if (next == std::string_view::npos) {
      break;
    }
    pos = next + 1;
  }
  return out;
}

static const char* elem_types[] = {
    "NORMAL",      "PICTURES", "LINK", "REFER_INLINE",
    "MATH_INLINE", "MATH",     "BOLD", "ITALIC",
};

static const char* elem_envs[] = {
    "NORMAL", "REFER", "REFER_CROSS", "CODE", "TITLE", "OLIST", "ULIST",
};

auto operator<<(std::ostream& os, const ElemType type) -> std::ostream& {
  os << elem_types[static_cast<int>(type)];
  return os;
}

auto operator<<(std::ostream& os, const ElemEnv env) -> std::ostream& {
  os << elem_envs[static_cast<int>(env)];
  return os;
}
