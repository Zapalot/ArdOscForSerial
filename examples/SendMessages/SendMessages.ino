// How to send OSC messages from an Arduino.
// !The Adapter must already be configured before this Sketch works! (i.e. using the example in the MinimalWifly library)

// This example has been tested using a Roving Networoks "Wifly" Wireless Adapter
// This Example is in the public domain.

#include <ArdOSCForSerial.h>

//Configuration:
int ledPin=13;
int networkTxPin=2; // the pin that sends data to the network adapter
int networkRxPin=3; // the pin that receives data from the network adapter
unsigned long networkBaudrate =19200;      // Speed of the Serial connection to the network adapter. 19200 is the maximum that works reliably with a Software Serial. 
unsigned long networkTimeoutMillis=3;      // How long the Network adapter waits until it flushes the Buffer and sends an UDP-Package.
// we use a software serial here - if you own a Mega or a Teensy, you want to change this to a Hardware UART.
#include "SoftwareSerial.h" 
SoftwareSerial networkSerial(networkRxPin,networkTxPin); // we assume an already configured network module to be connected to this port.
OSCClient client(&networkSerial,networkTimeoutMillis); // this "OSCClient" object will wrap up the data into an OSC Message and pass it to the netowrk interface

void setup()
{ 
  Serial.begin(115200);                 //initialize connection to PC
  networkSerial.begin(networkBaudrate); //initalize connection to network adapter
}


void loop()
{
  Serial.println("Sending message...");
  // note that the destination adress is set by setting the remote host of the network interface! 
  // this has to be done with a different program!
  
  // there are two ways of sending messages:
  
  // 1. simple but not as flexible: the convenience functions "sendInt" and "sendFloat"
  client.sendInt(analogRead(A0),"/ard/A0Value");
  client.sendFloat((float)analogRead(A1)*5.0/255.0,"/ard/A1Voltage");
  
  // 2. Using a local message object allows to multiple additional parameters in a single message:
  // The maximum number of Arguments can be set in the file "OSCCommon.h" in the line #define kMaxAugument	8
  OSCMessage localMess;
  localMess.beginMessage("/ard/A2A3Value");
  localMess.addArgInt32(analogRead(A2));
  localMess.addArgInt32(analogRead(A3));
  client.send(&localMess);
}



