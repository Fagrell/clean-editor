#pragma once

#include <QObject>
#include <QString>
#include <QUrl>

#include "globals.h"

namespace CleanEditor::Logic {

class CLEAN_EDITOR_EXPORT FileHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FileHandler)

    Q_PROPERTY(QString fileName READ fileName NOTIFY fileUrlChanged)
    Q_PROPERTY(QString fileType READ fileType NOTIFY fileUrlChanged)
    Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString data READ data)

public:
    explicit FileHandler(QObject *parent = nullptr);

    QString fileName() const;
    QString fileType() const;
    QUrl fileUrl() const;
    QString data() const;

public Q_SLOTS:
    void load(const QUrl &file_url);
    bool saveAs(const QUrl &file_url, const QString &data);
    bool save(const QString &data);

Q_SIGNALS:
    void fileUrlChanged();
    void fileOpened();
    void error(const QString &message);

private:
    QUrl file_url_;
    static QString localPathFromUrl(const QUrl &file_url);
};

} //namespace CleanEditor::Logic
