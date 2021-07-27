#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <interface.h>

class Translator : public ITranslator {
public:
  Translator() = default;
  ~Translator() = default;
  auto translate(const std::vector<std::vector<Element>> lines) const
      -> std::string override;

  auto save(const std::string& path) const -> bool override;

private:
  std::string last_result;
  std::string last_path;
};

#endif // TRANSLATOR_H
