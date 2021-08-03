#include <page.h>
#include <QDesktopServices>

Page::Page(QObject* parent) : QWebEnginePage(parent) {}

auto Page::acceptNavigationRequest(const QUrl& url,
                                   QWebEnginePage::NavigationType _type,
                                   bool _isMainFrame) -> bool {
  // Only allow qrc:/index.html.
  if (url.scheme() == QString("qrc")) {
    return true;
  }
  QDesktopServices::openUrl(url);
  return false;
}
