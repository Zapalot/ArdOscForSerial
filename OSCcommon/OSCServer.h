/*
 
 ArdOSC 2.1 - OSC Library for Arduino.
 
 -------- Lisence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2011 recotana( http://recotana.com )　All right reserved
 
 */

#ifndef ArdOSC_OSCServer2_h
#define ArdOSC_OSCServer2_h


#include "OSCcommon.h"
#include "OSCMessage.h"
#include "OSCDecoder.h"
#include "Pattern.h"


class OSCServer{
    
private:

    Stream* networkStream;

    char _rcvData[kMaxRecieveData];

    OSCDecoder::OSCDecoder _decoder;
    Pattern::Pattern _adrMatch;

public:
    
    OSCServer(Stream* networkStream, ///< where to get messages from
	unsigned long receiveTimeOut=3   ///< how long to wait until reception is finished
	);
    ~OSCServer(void);
    unsigned long receiveTimeOut;
    bool availableCheck(
		//adjust the timeout to your Baudrate for best performance.
		//recommended values are:
		//9600 baud: 3ms
		//115200 baud: 1ms
	);

    //_adr osc address string pointer - "/ard/aaa"
    //_func callback function pointer
    void addCallback(char *_adr , Pattern::AdrFunc _func);
	void addOscMessageSink(OscMessageSink* sink );

};


#endif
