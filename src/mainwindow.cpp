#include <QWebChannel>
#include <QFileDialog>
#include <QMessageBox>

#include <mainwindow.h>
#include "../forms/ui_mainwindow.h"
#include <page.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), parser(new Parser),
      translator(new Translator), content(new Document(this)) {
  ui->setupUi(this);
  ui->viewer->setContextMenuPolicy(Qt::NoContextMenu);

  auto page = new Page(this);
  auto channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("content"), content);
  ui->viewer->setPage(page);
  page->setWebChannel(channel);

  ui->viewer->setUrl(QUrl("qrc:/index.html"));
  setWindowTitle("Ipora");
  setWindowIcon(QIcon(":app.ico"));
}

MainWindow::~MainWindow() {
  delete ui;
  delete parser;
  delete translator;
}

inline auto MainWindow::is_modified() const -> bool {
  return ui->editor->document()->isModified();
}

inline auto MainWindow::save(const QString& path) -> void {
  auto file = QFile(path);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QMessageBox::warning(this, windowTitle(), "Couldn't write file.");
    return;
  }
  auto os = QTextStream(&file);
  os << ui->editor->toPlainText();

  ui->editor->document()->setModified(false);
}

void MainWindow::on_actionOpen_triggered() {
  if (is_modified()) {
    auto ret = QMessageBox::question(
        this, windowTitle(),
        "You have unsaved changes.\n"
        "Do you want to discard all changes and open new document?");
    if (ret != QMessageBox::Yes) {
      return;
    }
  }

  auto path =
      QFileDialog::getOpenFileName(this, "Open", "", "Markdown File(*.md)");
  auto file = QFile(path);

  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, windowTitle(), "could not open file");
    return;
  }

  last_path = path;
  ui->editor->setPlainText(file.readAll());
}

auto MainWindow::on_actionSave_triggered() -> void {
  if (!is_modified()) {
    return;
  }
  if (!last_path.isEmpty()) {
    save(last_path);
    return;
  }

  auto path =
      QFileDialog::getSaveFileName(this, "Save", "", "Markdown File(*.md)");
  if (path.isEmpty()) {
    return;
  }
  last_path = path;
  save(path);
}

void MainWindow::on_actionSave_as_triggered() {
  auto path =
      QFileDialog::getSaveFileName(this, "Save As", "", "Markdown File(*.md)");
  if (path.isEmpty()) {
    return;
  }
  last_path = path;
  save(path);
}

void MainWindow::on_actionClose_triggered() {
  if (is_modified()) {
    auto ret =
        QMessageBox::question(this, windowTitle(),
                              "You have unsaved changes.\n"
                              "Do you want to discard all changes and exit?");
    if (ret != QMessageBox::Yes) {
      return;
    }
  }
  close();
}

void MainWindow::on_actionAbout_triggered() {
  QMessageBox::about(this, "About Ipora",
                     "A simple markdown editor made by Iori.");
}

void MainWindow::on_actionAbout_Qt_triggered() { QMessageBox::aboutQt(this); }

void MainWindow::on_editor_textChanged() {
  parser->set(ui->editor->toPlainText().toStdString());
  auto out = translator->translate(parser->parse());
  content->setText(QString::fromStdString(out));
}
