Air Quality Egg DataLogger
===========================
This Arduino/Nanode project reuses the shield and code of AQE to log sensor data to a file in SD card

The original code of AQE can be found at http://bit.ly/AQE-CODE
More information about the AQE project (in Spanish) can be found at http://ks380570.kimsufi.com/foswiki/bin/view/DCDCity/WebHome

The project has been tested in one Arduino Uno board instead of the original Nanode board. 
Although the code has not been tested on the Nanode board, it should be compatible and should nor tequire any chages.

The project uses the MP3 shield of Sparkfun Electronics for the SD card reader https://www.sparkfun.com/products/10628

Changes to additional code 
--------------------------
The Nanode Ethernet library is removed. Instead the offical Arduino SD library is included. 
As a consequence, the nanode.ino sketch file is replaced by SDlog.ino wherethe methods nanodeSetup() and nanodeSendData() implement SD functionality instead of the original Ethernet functions.
Sensor data is written to DATALOG.TXT in csv format:

		Current time,NO2,CO,airQuality,humidity,temperature,button

		1981,0,0,0,0,0,0
		11982,129,15,181,40,21,0
		21983,130,15,177,40,21,0
		31984,130,15,196,41,21,0
		41985,131,15,206,39,21,0
		51986,131,15,189,40,21,0
		61987,132,15,191,40,21,0
		71988,128,19,151,40,21,0
		81989,128,12,129,40,21,0
		91990,128,10,133,40,21,0

The project uses the SD reader of Sparkfun MP3 shield where digital PIN 9 is used as chip select (SS) of the SPI protocol. 
However PIN 9 is used to control the statusLed in the original AQE design. To avoid this conflict, statusLed has been moved to PIN 8 (updated the definition of statusLed in LEDs.ino and changed the wired connection in the shield).
		
Known Issues/Improvements
---------------------------
- There is no Real Time Clock (RTC) available in Arduino. It would be good to add one RTC to the project to obtain precise timing data

License
-------------
Copyright 2012 Javier Montaner
The same license of the original AQE project applies to this modified version