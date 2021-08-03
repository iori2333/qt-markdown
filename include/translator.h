#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <interface.h>

class Translator : public ITranslator {
public:
  Translator() = default;
  ~Translator() = default;
  auto translate(const std::vector<std::vector<Element>>& lines)
      -> std::string override;

  auto save(const std::string& path) const -> bool override;

private:
  std::string last_result;

  auto translate_line(const std::vector<Element>& line,
                      bool ignore_first = false) const -> std::string;
  auto translate_element(const Element& element) const -> std::string;
};

#endif // TRANSLATOR_H
