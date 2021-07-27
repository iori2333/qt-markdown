// #include "mainwindow.h"
#include <parser.h>
// #include <QApplication>

// int main(int argc, char* argv[]) {
//  QApplication a(argc, argv);
//  MainWindow w;
//  w.show();
//  return a.exec();
//}

auto main(int argc, char** argv) -> int {
  auto parser = std::shared_ptr<IParser>();
  parser.reset(new Parser());

  parser->set("```\n# 123\n```\n\n# `123`");
  auto p = parser->parse();
}
