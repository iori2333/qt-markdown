#ifndef PAGE_H
#define PAGE_H
#include <QWebEnginePage>

class Page : public QWebEnginePage {
  Q_OBJECT
public:
  explicit Page(QObject* parent = nullptr) : QWebEnginePage(parent) {}
  ~Page() = default;

protected:
  bool acceptNavigationRequest(const QUrl& url, NavigationType type,
                               bool isMainFrame);
};

#endif // PAGE_H
