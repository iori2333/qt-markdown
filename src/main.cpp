#include <QApplication>

#include <mainwindow.h>
#include <parser.h>
#include <translator.h>

auto main(int argc, char* argv[]) -> int {
  auto a = QApplication(argc, argv);
  auto w = MainWindow();
  w.show();
  return a.exec();
}
