#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

enum class ElemType {
  NORMAL = 0,   // regular texts
  PICTURE,      // pictures
  LINK,         // links
  REFER_INLINE, // inline references
  MATH_INLINE,  // inline LaTeX
  MATH,         // multi-line LaTeX
  BOLD,         // bold texts
  ITALIC,       // italic texts
};

enum class ElemEnv {
  NORMAL = 0, // regular environment
  REFER,      // reference environment
  CODE,       // code environment
  TITLE,      // titles
  OLIST,      // ordered lists
  ULIST,      // unordered lists
};

struct Element {
  std::string content;
  ElemEnv env;
  ElemType type;
};

#endif // ELEMENT_H
