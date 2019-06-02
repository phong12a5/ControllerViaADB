#ifndef REGCONTROLLERBASE_H
#define REGCONTROLLERBASE_H

#include <QObject>

class RegControllerBase : public QObject
{
    Q_OBJECT
public:
    explicit RegControllerBase(QObject *parent = nullptr);

signals:

public slots:
    virtual void onCurrentActivityChanged() = 0;
};

#endif // REGCONTROLLERBASE_H
