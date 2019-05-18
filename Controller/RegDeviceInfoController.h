#ifndef REGDEVICEINFOCONTROLLER_H
#define REGDEVICEINFOCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "AppEnums.h"

class RegDeviceInfoController : public QObject
{
    Q_OBJECT
private:
    explicit RegDeviceInfoController(QObject *parent = nullptr);

public:
    static RegDeviceInfoController* instance();

    void initRegDeviceInfoController();
private:
    static RegDeviceInfoController* m_intance;

signals:

public slots:
    void onCurrentActivityChanged();
};

#endif // REGDEVICEINFOCONTROLLER_H
