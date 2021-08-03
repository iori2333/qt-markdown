#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <vector>

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
  NORMAL = 0,  // regular environment
  REFER,       // reference environment
  REFER_CROSS, // cross reference (self-made)
  CODE,        // code environment
  TITLE,       // titles
  OLIST,       // ordered lists
  ULIST,       // unordered lists
};

struct Element {
  std::string content;
  ElemEnv env;
  ElemType type;
};

using ElemLine = std::vector<Element>;
using ElemLines = std::vector<ElemLine>;

#endif // ELEMENT_H
