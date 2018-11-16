#include "realtime.h"
#include <QDebug>

#if defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(_M_ARM) || defined(__aarch64__)
#define MOCK false
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
#define MOCK true
#endif

Realtime::Realtime(QObject *parent)
    : QObject(parent)
    , _accx(0)
    , _accy(0)
    , _accz(0)
    , _girox(0)
    , _giroy(0)
    , _giroz(0)
{
    init();
}

Realtime::~Realtime()
{

}

void Realtime::init()
{
    QString path;

    if (MOCK) {
        path = "mock.data";
        qDebug() << "Started with mock data";
    } else {
        path = "/dev/ttyRPMSG";
    }
    rpmsgDevice.setFileName(path);

    if (rpmsgDevice.open(QIODevice::ReadWrite)){
        qDebug() << "RPMSG Device is Open";
    } else {
        qDebug() << "Error: could not open RPSMG Device";
    }
    qDebug() << "started Realtime";
}

void Realtime::update()
{
    qDebug() << "Get Sensor Realtime Data";
    if(!rpmsgDevice.isOpen()){
        qDebug() << "RPMSG Device not open";
    } else {

        int accx, accy, accz;

        if (!MOCK) {
            QByteArray query("acc");
            rpmsgDevice.write(query);
            rpmsgDevice.flush();
        }
        QByteArray response = rpmsgDevice.readLine(64);
        sscanf(response.constData(),
               "x:%d,y:%d,z:%d", &accx, &accy, &accz);
        if(accx != _accx || accy != _accy || accz != _accz){
            _accx = accx;
            _accy = accy;
            _accz = accz;
        }

        /*
        int girox, giroy, giroz;
        query = "?giro";
        rpmsgDevice.write(query);
        rpmsgDevice.flush();
        response = rpmsgDevice.readLine(64);
        sscanf(response.constData(),
               "?x:%d,y:%d,z:%d", &girox, &giroy, &giroz);
        if(girox != _girox || giroy != _giroy || giroz != _giroz){
           _girox = girox;
           _giroy = giroy;
           _giroz = giroz;
           emit giroChanged();
        }
        */
        if (MOCK) if (rpmsgDevice.atEnd()) rpmsgDevice.seek(0);
    }
}

int Realtime::XAcc() const
{
    return _accx;
}

int Realtime::YAcc() const
{
    return _accy;
}

int Realtime::ZAcc() const
{
    return _accz;
}

int Realtime::XGiro() const
{
    return _girox;
}
int Realtime::YGiro() const
{
    return _giroy;
}
int Realtime::ZGiro() const
{
    return _giroz;
}
