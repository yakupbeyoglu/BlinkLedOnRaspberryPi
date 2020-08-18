#include "controller.h"
#include <QTimer>

controller::controller(QObject *parent)
{
        /// below lines used for blink led without library !
        /*QFile file("/sys/class/gpio/export");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
               exit(1);
        QTextStream out(&file);
        out<<"24";
        file.close();
        QFile direction("/sys/class/gpio/gpio24/direction");
        if(!direction.open(QIODevice::WriteOnly | QIODevice::Text))
                exit(1);
       QTextStream outdirection(&direction);
       outdirection<<"out";
       direction.close();*/
       wiringPiSetup();
       wiringPiSetupGpio();
       ///pin 2 for button
       pinMode(2,INPUT);
       ///pin 24 for led
       pinMode(24,OUTPUT);
     QTimer *timer = new QTimer(this);
     QObject::connect(timer,SIGNAL(timeout()),this,SLOT(statusofbutton()));
     timer->start(150);


}

void
controller::blinkLed() {
         digitalWrite(24,!digitalRead(24));
}
void
controller::setStatus(const bool &tstatus)
{
        status = tstatus;

}
void
controller::toogle()
{
        status = !status;
}

void
controller::turnOff()
{
        digitalWrite(24,0);
}
void
controller::toogleStatus(const bool &stat)
{
   setStatus(stat);
  // Open();
   if(status)
      blinkLed();
   else {
           status = false;
           turnOff();


   }

   emit statusChanged();

}
void
controller::statusofbutton()
{
        toogleStatus(digitalRead(2)==0);

}



bool
controller::getStatus()const
{
        return status;
}



