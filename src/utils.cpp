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

auto replace_string(std::string& s, std::string_view from, std::string_view to)
    -> void {
  auto pos = 0llu;
  while (pos < s.size()) {
    pos = s.find(from, pos);
    if (pos == std::string::npos) {
      break;
    }
    s.replace(pos, from.size(), to);
    pos += to.size();
  }
}
