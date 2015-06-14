#include <SoftwareSerial.h>
#include "bluetooth.h"

Bluetooth *blue = new Bluetooth("ExampleRobot");


void setup(){
	Serial.begin(9600);
	blue->setupBluetooth();	
}


void loop(){
//	char msg = blue->ReadFrom();
//	if((int)msg != -1){
//		Serial.print("Received: ");
//		Serial.println(msg);
//	}

        String msg = blue->Read();
	if(msg.length() > 1){
		Serial.print("Received: ");
		Serial.println(msg);
	}

	if(Serial.available()){
                char toSend = (char)Serial.read();
                Serial.println(toSend);
//		blue->SendTo(to  Send);
//                blue->SendInformation("tutu", 4, Bluetooth::ACCELERATION);
//                blue->Send("Messsage");
                blue->SendAngle(12.12, 13.13, 14.14);
                
	}
}

