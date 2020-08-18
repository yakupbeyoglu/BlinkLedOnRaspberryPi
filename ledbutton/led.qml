import QtQuick 2.0

Item {


        function toogle(){
                if(!test.tstatus)
                        bulb.source = "images/off.png";
                else
                        bulb.source = "images/on.png";



        }

        Text{

                text:"Status = "+test.tstatus;


                font.pointSize: 20;
                x:100;
                color:"Red";

        }
        Image{
               width:200;
               height:200;
                id: bulb
                source:"images/off.png";
                x:200;
                y:150;

        }

        Timer {
                id: light
                repeat: true
                running: true
                interval: 150
                onTriggered: toogle()
        }


}

