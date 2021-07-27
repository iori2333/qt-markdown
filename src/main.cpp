// #include "mainwindow.h"
#include <parser.h>
#include <translator.h>
// #include <QApplication>

// int main(int argc, char* argv[]) {
//  QApplication a(argc, argv);
//  MainWindow w;
//  w.show();
//  return a.exec();
//}

auto main(int argc, char** argv) -> int {
  auto parser = std::shared_ptr<IParser>(new Parser());
  auto translator = std::shared_ptr<ITranslator>(new Translator());

  parser->set("# Title\n> author: `Iori`\nlink: [github](github.com)\n## Title 2\nabaaba\n");
  auto p = parser->parse();
  translator->translate(p);
}
