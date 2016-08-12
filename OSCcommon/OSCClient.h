/*
 
 ArdOSC 2.1 - OSC Library for Arduino.
 
 -------- Lisence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2011 recotana( http://recotana.com )　All right reserved
 
 */

#ifndef ArdOSC_OSCClient2_h
#define ArdOSC_OSCClient2_h

#include "Arduino.h"
#include "OSCcommon.h"
#include "OSCMessage.h"
#include "OSCEncoder.h"


#define kDummyPortNumber 10000


class OSCClient{
    
private:

    Stream* networkStream;

    OSCEncoder encoder;
	unsigned long lastSendMillis;	        ///< used to make sure that the Wifly sends each message in a single package.
	unsigned long networkStreamTimeoutMillis;	///< if we wait that long between messages, an UDP package is sent. (At least if you use a wifly)
public:

    OSCClient(Stream* networkStream,unsigned long networkStreamTimeoutMillis);
    ~OSCClient(void);
    int send(OSCMessage *_message);	
	int sendInt(int value, char* adress);	 ///< send a single number to the specified adress conveniently
	int sendFloat(float value, char* adress);///< send a single number to the specified adress conveniently
};


#endif
