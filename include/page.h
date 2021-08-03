#ifndef PAGE_H
#define PAGE_H
#include <QWebEnginePage>

class Page : public QWebEnginePage {
  Q_OBJECT
public:
  explicit Page(QObject* parent = nullptr);
  ~Page() = default;

protected:
  auto acceptNavigationRequest(const QUrl& url, NavigationType type,
                               bool isMainFrame) -> bool;
};

#endif // PAGE_H
