readme.txt of the RTCscilab toolbox


This is the Toolbox for interconnect between RT (Robotics Technologies) Component and scilab.

Version: 0.7.5

Author: Yuki Suga <ysuga@ysuga.net>



1. Install

 RTC-scilab depends on following library

 scilab ( > 5.2.0)
 OpenRTM-aist C++ ( = 1.0 Release)
 


1.0 Install Dependencies

1.0.1 scilab
Download scilab and install.

http://www.scilab.org


1.0.2 OpenRTM-aist
Download OpenRTM-aist and install.

http://www.openrtm.org

The developmental environment is also necessary for the RTC-scilab as well as OpenRTM-aist library.
Install python, pyYaml, JDK6, and eclipse all in one package,


1.1 build
 
 Launch scilab, and change directory to the rtc_scilabXXX which is generated when you extract the downloaded archive file.
 Next, execute builder.sce script file (just input "exec builder.sce").
 Wait a minute, and you can see that the "loader.sce" script file is automatically generated if successfully built.


1.2 Copy to scilab contribution directory

 The RTC-scilab folder (or directory) that is previously built should be copied to the scilab's installed directory (not necessary but recommended).
 Usually scilab is installed in the following directory

 [Windows] C:\program files\scilab5.2.X
 [Linux] /usr/local/scilab5.2.X/share/scilab

 The installed directory can be confirmed by SCI value in scilab.
 For example, input in scilab command line as follows:
 
 --> SCI
  SCI =
 
  /usr/local/scilab5.2.2/share/scilab

 (*In windows operation system, WSI is also avaiable.)


 Please copy the built package to "SCI/contrib".

 Then, restart scilab. You can see the rtc_scilabXXX in the scilab main window's "toolbox" menu.


2 Tutorial


2.1 Load RTC-scilab toolbox

CAUTION!!
Before loading the RTC-scilab toolbox, please launch the Name Service. In Windows System, "Start Naming Service" script is simultaneously installed with OpenRTM-aist. In Linux, "rtm-naming" command executes omniNames daemon process. For more information, please refer the OpenRTM-aist official website (www.openrtm.org).

If you want to load RTC-scilab, select main menu "toolbox"--->"rtc_scilabXXX".
Then, you can see following message.

 Start RTCscilab Toolbox
	Load macros
	Load shared library
	Load help
	Load demos


2.2 Demo

Please click the "Gear" like icon that means "launch demos", then please select RTC-scilab toolbox demo.


