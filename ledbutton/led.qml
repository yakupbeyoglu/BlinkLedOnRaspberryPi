import QtQuick 2.0

Item {

property int s : 0
        function toogle(){
                if(!test.tstatus){
                        bulb.source = "images/off.png";
                        pwmbulb.source = "images/off.png";
                        s=0;


                }
                else{
                        bulb.source = "images/on.png";
                        pwmbulb.source = "images/on.png";
                        if(s==0) {
                                s=1;
                                pwmbulb.opacity = 0;
                        }
                }


        }
        function opacity(){
                pwmbulb.opacity = (pwmbulb.opacity ==0 ? 0.1 : pwmbulb.opacity*2);
        }

        Text{

                text:"Status = "+test.tstatus;


                font.pointSize: 30;
                x:500;
                y: 50
                color:"Red";

        }
        Image{
               width:400;
               height:400;
                id: bulb
                source:"images/off.png";
                x:200;
                y:150;

        }

        Text{
                id:pwmtext
                text: "pwm value = "+(test.tstatus === 1 ? 0 : test.pwm);
                color : "black"
                x:850;
                y:600;
        }

        Image{
                width:400;
                height:400;
                id:pwmbulb
                source:"images/off.png";
                x:700;
                y:150;
        }

        Timer {
                id: light
                repeat: true
                running: true
                interval: 150
                onTriggered: toogle()
        }
        Timer{
                id:lightpwm
                repeat: true
                running:true
                interval:150
                onTriggered: opacity()
        }


}

