#ifndef MENU_MODEL_H
#define MENU_MODEL_H

#include "globals.h"

#include <QString>
#include <QObject>

class QTextDocument;

namespace CleanEditor {
namespace Models {

class QML_EDITOR_EXPORT MenuModel : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MenuModel)

  Q_PROPERTY(QString title READ title NOTIFY titleChanged)
  Q_PROPERTY(bool isNewFile READ isNewFile NOTIFY isNewFileChanged)

public:
  explicit MenuModel(QObject* parent = nullptr);

  QString title() const;
  void setTitle(const QString& text);

  bool isNewFile() const;
  void setIsNewFile(bool is_new_file);

Q_SIGNALS:
  void titleChanged();
  void isNewFileChanged();

private:
  QString title_;
  bool is_new_file_{false};
};

} // namespace Models
} // namespace CleanEditor

#endif
