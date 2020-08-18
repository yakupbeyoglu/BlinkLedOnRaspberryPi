#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QtDebug>
#include <QString>
#include <QFile>
#include <wiringPi.h>

class controller:public QObject
{
        Q_OBJECT
        public:

        Q_PROPERTY(bool tstatus  READ  getStatus NOTIFY statusChanged);
        Q_PROPERTY(int pwm READ getPwmValue NOTIFY pwmChanged);
        explicit controller(QObject *parent = 0);
                void setStatus(const bool &tstatus);
                bool getStatus()const;
                void blinkLed();
                void turnOff();
                void blinkLedPwm();
                int getPwmValue()const;


        public slots :
                void  toogleStatus(const bool &stat);
                void statusofbutton();


         signals:
                void callsignal(const QString txt);
                void statusChanged();
                void pwmChanged();

        private:
                bool status = false;
                void toogle();
                int pwm = 0;



};

#endif // CONTROLLER_H
