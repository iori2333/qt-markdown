#include <utils.h>

auto utils::split(std::string_view s, std::string_view delims)
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
