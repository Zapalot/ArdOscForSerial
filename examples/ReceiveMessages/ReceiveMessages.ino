// Shows how to receive OSC messages from Network adapter connected by a Serial interface.
// !The Adapter must already be configured before this Sketch works! (i.e. using the example in the MinimalWifly library)
// The example has been tested using a Roving Networoks "Wifly" Wireless Adapter.
// This Example is in the public domain.

// Important known issues:
// The Wifly provides no means to get the data from a single UDP package at a time
// Everything is just dumped to the serial connection.
// The only hint that a package is finished is that reading from the serial *might* time out
// To make things work anyway:
// 1. Use a high baud rate for communication with the Wifly: 115200 on a hardware serial is perfect.
// 2. Adjust the timeout in server.availableCheck(). 2ms works fine with 115200baud.
// 3. If possible, let the controlling Program pause at least 1.5 times the timout between sending OSC messages.

#include <ArdOSCForSerial.h>

//Configuration:
int ledPin=13;
int networkTxPin=2; // the pin that sends data to the network adapter
int networkRxPin=3; // the pin that receives data from the network adapter
unsigned long networkBaudrate =19200;      // Speed of the Serial connection to the network adapter. 19200 is the maximum that works with a Software Serial. 
unsigned long networkTimeoutMillis=3;      // How long to wait for an UDP-Package to finish. Play with this value if you loose messages
// we use a software serial here - if you own a Mega or a Teensy, you want to change this to a Hardware UART.
#include "SoftwareSerial.h" 
SoftwareSerial networkSerial(networkRxPin,networkTxPin); // we assume an already configured network module to be connected to this port.
OSCServer server(&networkSerial,networkTimeoutMillis);   // the OSC Server will get it's data from the Serial passed to it.
// If 

void setup()
{ 
  Serial.begin(115200);                 //initialize connection to PC
  networkSerial.begin(networkBaudrate); //initalize connection to network adapter

  // OSC-Reception works unsing so called "Callback Functions":
  // You tell the OSC-Server an OSC Adress and a Function, and it will invoke that Funktion when it receives a Packet with that adress:
  // When a message is with the adress string "/ard/ledFade" is received, the function "setLedFade" will be invoked.
  server.addCallback("/ard/ledFade",&setLedFade);
}


void loop()
{

  // If a message with a registered adress is received, the Server will callback function (in this case setLedFade()) will be invoked.
  server.availableCheck(); //check for new incoming messages.
}

void setLedFade(OSCMessage *_mes){
  //get 1st argument(int32) and use it to fade the LED. Other Argument types are getArgFloat or getArgString
  int fadeValue=_mes->getArgInt32(0); // the '->' allows access to functions of the message that was passsed as a pointer (*). 
  Serial.println(fadeValue);
  analogWrite(ledPin,fadeValue );
}


