#ifndef REGFBCONTROLLER_H
#define REGFBCONTROLLER_H

#include <QObject>
#include "AppDefines.h"

class RegFBController : public QObject
{
    Q_OBJECT
private:
    explicit RegFBController(QObject *parent = nullptr);

public:
    static RegFBController* instance();

    void initRegFBController();

private:
    static RegFBController* m_intance;

public slots:
    void onCurrentActivityChanged();
};

#endif // REGFBCONTROLLER_H
