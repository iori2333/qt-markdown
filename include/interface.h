#ifndef INTERFACE_H
#define INTERFACE_H

#include <element.h>
#include <vector>

class IParser {
public:
  virtual ~IParser() = default;

  virtual auto set(std::string_view text) -> void = 0;

  virtual auto parse() const -> std::vector<std::vector<Element>> = 0;
};

class ITranslator {
public:
  virtual ~ITranslator() = default;

  virtual auto translate(const std::vector<std::vector<Element>>& lines)
      -> std::string = 0;

  virtual auto save(const std::string& path) const -> bool = 0;
};

#endif // INTERFACE_H
