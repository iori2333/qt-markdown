#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <parser.h>
#include <translator.h>
#include <document.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionOpen_triggered();
  void on_actionSave_triggered();
  void on_actionSave_as_triggered();
  void on_actionClose_triggered();
  void on_actionAbout_triggered();
  void on_actionAbout_Qt_triggered();
  void on_editor_textChanged();

private:
  Ui::MainWindow* ui;
  IParser* parser;
  ITranslator* translator;
  Document* content;
  QString last_path;

  inline auto is_modified() const -> bool;
  inline auto save(const QString& path) -> void;
};
#endif // MAINWINDOW_H
