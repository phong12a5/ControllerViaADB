#ifndef REGDEVICEINFOCONTROLLER_H
#define REGDEVICEINFOCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "AppEnums.h"
#include "Base/RegControllerBase.h"

class RegDeviceInfoController : public RegControllerBase
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
    void onCurrentActivityChanged() override;
};

#endif // REGDEVICEINFOCONTROLLER_H
