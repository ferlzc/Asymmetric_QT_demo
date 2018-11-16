#ifndef REALTIME_H
#define REALTIME_H

#include <QTimer>
#include <QObject>
#include <QFile>

class Realtime : public  QObject
{
    Q_OBJECT
    Q_PROPERTY(int accX READ XAcc NOTIFY accChanged)
    Q_PROPERTY(int accY READ YAcc NOTIFY accChanged)
    Q_PROPERTY(int accZ READ ZAcc NOTIFY accChanged)
    Q_PROPERTY(int giroX READ XGiro NOTIFY giroChanged)
    Q_PROPERTY(int giroY READ YGiro NOTIFY giroChanged)
    Q_PROPERTY(int giroZ READ ZGiro NOTIFY giroChanged)

public:
    Realtime(QObject *parent = nullptr);
    virtual ~Realtime();
    int XAcc() const;
    int YAcc() const;
    int ZAcc() const;
    int XGiro() const;
    int YGiro() const;
    int ZGiro() const;

private:
    QFile rpmsgDevice;

    int _accx;
    int _accy;
    int _accz;
    int _girox;
    int _giroy;
    int _giroz;

    void get_data();
    void get_data_mock();

signals:
    void accChanged();
    void giroChanged();

public slots:
    void init();
    void update();
};

#endif // REALTIME_H
