#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

enum class ElemType {
  NORMAL = 0,   // regular text
  OLIST,        // ordered list
  ULIST,        // unordered list
  TITLE,        // title
  PICTURE,      // picture
  LINK,         // link
  REFER_INLINE, // inline reference
  MATH_INLINE,  // inline LaTeX
  MATH,         // multi-line LaTeX
  BOLD,         // bold texts
  ITALIC,       // italic texts
};

enum class ElemEnv {
  NORMAL = 0, // regular environment
  REFER,      // reference environment
  CODE,       // code environment
};

struct Element {
  std::string content;
  ElemEnv env;
  ElemType type;
};

#endif // ELEMENT_H
