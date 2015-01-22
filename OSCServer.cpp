/*
 
 ArdOSC 2.1 - OSC Library for Arduino.
 
 -------- Lisence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2011 recotana( http://recotana.com )　All right reserved
 
 */

#include <stdlib.h>

#include "OSCcommon/OSCServer.h"


OSCServer::OSCServer(Stream* networkStream,unsigned long receiveTimeOut) :
 networkStream(networkStream),
 receiveTimeOut(receiveTimeOut)
{

}


OSCServer::~OSCServer(void)
{

}



bool OSCServer::availableCheck()
{

    if( networkStream->available() == 0 )
    {
      return false;
    }
	//Serial.println("building osc message");delay(40);
    OSCMessage rcvMes;

    //get max receive data
	//Serial.println("reading data from wifly...");delay(10);
	networkStream->setTimeout(receiveTimeOut);
    networkStream->readBytes(_rcvData, kMaxRecieveData); 
	
	//Serial.println(_rcvData);
    //clear input buffer
	//Serial.println("flushing remaining data from wifly...");delay(10);
	while(networkStream->available()){networkStream->read();} //flush everything that came later.

    //decode message
	//Serial.println("fdecoding osc message...");delay(10);
    if( _decoder.decode(&rcvMes, (uint8_t*)_rcvData) < 0 )
    {
      return false;
    }
	//Serial.println("Adress:");
	//Serial.println(rcvMes.getOSCAddress());
	//Serial.println("matching to routing table...");delay(10);
    _adrMatch.paternComp(&rcvMes);

    return true;
}


void OSCServer::addCallback(char *_adr , Pattern::AdrFunc _func )
{
    _adrMatch.addOscAddress(_adr, _func);
}

void OSCServer::addOscMessageSink(OscMessageSink* sink )
{
    _adrMatch.addOscMessageSink(sink);
}
