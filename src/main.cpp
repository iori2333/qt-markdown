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
  auto parser = Parser();
  parser.set("# abc\n## fff\n### ll");
  auto p = parser.parse();
}
