
/*  PulseSensor Starter Project and Signal Tester
 *  The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.
 *
 *  Here is a link to the tutorial
 *  https://pulsesensor.com/pages/code-and-guide
 *
 *  WATCH ME (Tutorial Video):
 *  https://www.youtube.com/watch?v=RbB8NSRa5X4
 *
 *
-------------------------------------------------------------
1) This shows a live human Heartbeat Pulse.
2) Live visualization in Arduino's Cool "Serial Plotter".
3) Blink an LED on each Heartbeat.
4) This is the direct Pulse Sensor's Signal.
5) A great first-step in troubleshooting your circuit and connections.
6) "Human-readable" code that is newbie friendly."

*/
#include <Wire.h>
#include "mySensor.h"
#include "Firebase.h"



Firebase *myfirebase;

int GSRpin=34;
MAX30105_sensor *max30105;
GSR_Sensor *myGSR_Sensor;
// The SetUp Function:
void setup() {
  
  Serial.begin(115200);         // Set's up Serial Communication at certain speed.
  delay(500);
  Serial.println("Serial begin........");
  // Wire.begin();
  // Serial.println("Wire begin.....");
  max30105=new MAX30105_sensor();
  myGSR_Sensor= new GSR_Sensor(GSRpin);
  myfirebase=new Firebase();
}
int i=0;
int loopdelay=100;
int upload_interval=1000;
int looptimes=0;
// The Main Loop Function
void loop() {


                    
  // Serial.println("BLE working");
  // Serial.println("Serial Working");
  // delay(5);
  max30105->read_data();

  // float conductivevoltage;
  // int GSRvalue;
  // GSRvalue=analogRead(GSR);
  // conductivevoltage = GSRvalue*(5.0/1023.0);
  if(looptimes>=upload_interval/loopdelay){
    myfirebase->SendData("GSR",String(myGSR_Sensor->get_filtereddata()),"GSR");
    myfirebase->SendData("HeartRate",String(max30105->getBPM()),"HeartRate");
    looptimes=0;
  }
  // Serial.print("GsrValue=");
  // Serial.println(GSRvalue);
  myGSR_Sensor->read_data();
  Serial.println(myGSR_Sensor->get_filtereddata());

  delay(loopdelay);
  looptimes++;

}
