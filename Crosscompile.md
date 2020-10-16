## Raspberry side (Client) : 

## first connect raspberry with ssh then; 
   sudo nano etcssh/ssh_config 
   sudo nano /etc/ssh/sshd_config
## find the line PermitRootLogin and make it comment out.  And cange front of to root login with yes. 
  # give new pass
   sudo passwd root
   sudo reboot
## uncomment last line which is about the apt-get update 
  nano etcapt/sources.list   
 apt-get dist-upgrade
 reboot
 rpi-update
 reboot
 ## qmake install
 sudo apt-get build-dep qt5-qmake 
 sudo apt-get build-dep libqt5webengine-data
 sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0 
 # create directiory of qt5pi
 mkdir /usr/local/qt5pi 
 chown -R root:root /usr/local/qt5pi 

## in Linux side ( Host ) ?
## for update
 apt-get update
## get upgrade from news
 apt-get -y upgrade  
## new packages
 apt-get install gcc git bison python gperf pkg-config 
## create directory on opt this will be in root directory cd ../../ or cd /
 sudo mkdir opt/qt5pi 
 sudo chown 1000:1000 opt/qt5pi
 cd opt/qt5pi
 git clone https://github.com/raspberrypi/tools 
 # nano ~/.bashrc 
 # add below line in the last part : 
 export PATH=$PATH:/opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin 
## above will give export path
## you can use reboot or re run bashrc file I am going to use re run 
. ~/.bashrc

## from this http://download.qt.io/official_releases/qt/ you need to select your version we are going to use qt5.12  you need qt-everywhere path that zip file for qt file which will we use for cross compile it will support qt required documents for compile
## download tar file from given link
wget download.qt.io/official_releases/qt/5.12/5.12.5/single/qt-everywhere-src-5.12.5.tar.xz 
tar xf qt-everywhere-5.12.5.tar.xz ##  if you download another version use your ##downloaded file name it will recompress your tar file

## below line copy linux arm file to new directory 
 cp -R qt-everywhere-src-5.12.5/qtbase/mkspecs/linux-arm-gnueabi-g++ qt-everywhere-src-5.12.5/qtbase/mkspecs/linux-arm-gnueabihf-g++

## with sed you can add or edit your text file in this line adding new config line in your qmake.conf file

 sed -i -e 's/arm-linux-gnueabi-/arm-linux-gnueabihf-/g' qt-everywhere-src-5.12.5/qtbase/mkspecs/linux-arm-gnueabihf-g++/qmake.conf 

## create new directory for rsync with your raspberry it will help to get important file from your remote !

 rsync -avz root@your_raspberry_pi_ip_address:/lib sysroot 

 rsync -avz root@your_raspberry_pi_ip_address:/usr/include sysroot/usr 

 rsync -avz root@your_raspberry_pi_ip_address:/usr/lib sysroot/usr 

 rsync -avz root@your_raspberry_pi_ip_address:/opt/vc sysroot/opt 

## move  libegl files with mv command

 mv sysroot/usr/lib/arm-linux-gnueabihf/libEGL.so.1.0.0 sysroot/usr/lib/arm-linux-gnueabihf/libEGL.so.1.0.0_backup 

## when you call libegls.so.1.0.0 automaticall call first line file 
## ln use for refer to other file
 ln -s sysroot/opt/vc/lib/libEGL.so sysroot/usr/lib/arm-linux-gnueabihf/libEGL.so.1.0.0 

 mv sysroot/usr/lib/arm-linux-gnueabihf/libGLESv2.so.2.0.0 sysroot/usr/lib/arm-linux-gnueabihf/libGLESv2.so.2.0.0_backup 

 ln -s sysroot/opt/vc/lib/libGLESv2.so sysroot/usr/lib/arm-linux-gnueabihf/libGLESv2.so.2.0.0 

 ln -s sysroot/opt/vc/lib/libEGL.so sysroot/opt/vc/lib/libEGL.so.1 

 ln -s sysroot/opt/vc/lib/libGLESv2.so sysroot/opt/vc/lib/libGLESv2.so.2 

 wget https://raw.githubusercontent.com/riscv/riscv-poky/master/scripts/sysroot-relativelinks.py 

## get executable mode
 chmod +x sysroot-relativelinks.py 
 ./sysroot-relativelinks.py sysroot 




## check your remote file again

 rsync -avz root@your_raspberry_pi_ip_address:/lib sysroot 

 rsync -avz root@your_raspberry_pi_ip_address:/usr/include sysroot/usr 

 rsync -avz root@your_raspberry_pi_ip_address:/usr/lib sysroot/usr 

 rsync -avz root@your_raspberry_pi_ip_address:/opt/vc sysroot/opt 
## re-run pythonn script

 ./sysroot-relativelinks.py sysroot 

## make directory for build and go that one 
 mkdir qt5build 
 cd qt5build 

## lets call configure file with your qt-everywhere file name if  you ae using any other rasp you need to change to infront of  -device to with below comments : 
	##raspbery pi 0  = linux-rasp-pi-g++
        ## raspberry pi 2 = linux-rasp-pi2-g++
        ## raspberry pi 3 = linux-rasp-pi3-g++
        ## vor pi3 + vc4 direver = linux-rasp-pi3-vc4-g++

 ../qt-everywhere-src-5.10.1/configure -opengl es2 -device linux-rasp-pi3-g++ -device-option CROSS_COMPILE=arm-linux-gnueabihf- -sysroot /opt/qt5pi/sysroot -prefix /usr/local/qt5pi -opensource -confirm-license -skip qtscript -nomake examples -make libs -pkg-config -no-use-gold-linker -v 
## for use four core make it with -j4 it will make your qmake file

 make -j8

 make install 

 cd /opt/qt5pi

 rsync -avz sysroot/usr/local/qt5pi root@10.80.1.217:/usr/local 


## after this one go your project file where qmake stay and call 
 /opt/qt5pi/sysroot/usr/local/qt5pi/bin/qmake 
## you will see make file
 make
## send your file to raspberry with ssh
 scp filename root@your_raspberry_pi_ip_address : ##here directroy if you give like that it will copy to home

# run with ./project name in your rasp

### Follow Below to add your Cross compile file To QT that means when you press debug, your project will work on the raspberry pi ! 
## if you want to use qt creator as cross compiler when press to run button follow below lines
## first go tools/options/ devices
## press Add and enter information dont forget username should be root !
## then enter kits>debuggers add  path : /opt/qt5pi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gdb
## Add c & c++ compilers 
# path: /opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++
# path: /opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc
## Add qtversions qmake file 
 # path : /opt/qt5pi/sysroot/usr/local/qt5pi/bin/qmake

## Add kits : 
# name : Raspberry pi 3
# device type : Generic Linux Device
# Device : Device name which did you write on device step
## system root file of your raspberry directory
sysRoot : /opt/qt5pi/sysroot 
## select your compilers which did you add above !
## select added debugger and qt version !
## END!
 













