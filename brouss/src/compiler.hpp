#ifndef COMPILER_H
#define COMPILER_H

#include <QObject>
#include <QDebug>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr) : QObject(parent) {}

    // Q_INVOKABLE makes this function callable from QML
    Q_INVOKABLE int launch(const QString &inputText);
    Q_INVOKABLE QString tokens_str(const QString &inputText);
    Q_INVOKABLE QString parse_str(const QString &inputText);
    Q_INVOKABLE QString assemble_str(const QString &inputText);
};

#endif // COMPILER_H
