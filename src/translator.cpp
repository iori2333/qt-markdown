#include <translator.h>
#include <utils.h>
#include <iostream>
#include <fstream>

auto Translator::translate(const std::vector<std::vector<Element>> lines) const
    -> std::string {
  for (auto&& line : lines) {
    for (auto&& elem : line) {
      auto&& [content, env, type] = elem;
      std::cout << "token: " << content << "\tenv: " << env
                << "\ttype: " << type << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
  }
  return "yes";
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
