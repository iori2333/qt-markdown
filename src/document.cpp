#include <document.h>

Document::Document(QObject* parent) : QObject(parent) {}

auto Document::setText(const QString& text) -> void {
  if (m_text == text)
    return;
  m_text = text;
  emit textChanged(m_text);
}
