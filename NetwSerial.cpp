#include "Arduino.h"
#include "NetwSerial.h"

//#define DEBUG

void NetwSerial::loop()  // TODO  server or client ???? call only when in parent mode
{
	#ifndef  __AVR_ATmega2560__
		while( Serial.available() )
		{
			pushChar((char)Serial.read());
		}
	#else
		while( serialPtr->available() )
		{
			pushChar((char)serialPtr->read());
		}
	#endif

	findPayLoadRequest();
	NetwBase::loop();
}

int NetwSerial::write( RxData *rxData ) // opt: 0=cmd, 1=val, 2=all
{
	rxData->msg.conn = nodeId;

	if(nodeId==0)
	{
		Serial.println(F("write.err nodeId==0"));
	}

	serialize( &rxData->msg, strTmp);

    // bool deb = false;

	#ifdef DEBUG
		//if(port!=0)deb=true;
		//Serial.print(F("Swite(")); Serial.print(port); Serial.print(F(") payld="));   Serial.print(str);Serial.flush();
	#endif

	#ifndef  __AVR_ATmega2560__
		Serial.println(strTmp);
	#else
		serialPtr->println(strTmp);
	#endif

	sendCount++;

	// netwTimer = millis() + NETW_SEND_SERIAL_DATA_INTERVAL;
	nextTimerMillis(NW_TIMER_BUSY, NETW_SEND_SERIAL_DATA_INTERVAL)	;	

	if(nodeId == rxData->msg.node ) nextTimer(NW_TIMER_PING, autoPing);	

	return 0;
}
//  id=isParent?81:82;
void NetwSerial::begin( )
{
//   id=isParent?83:84;
}

void NetwSerial::trace(const char* id)
{
	Serial.print(F("@ "));
	Serial.print(millis()/1000);
	Serial.print(F(" "));Serial.print(id);
	Serial.print(F(":node="));	 Serial.print(nodeId);
	// Serial.print(F(", nwTmr=")); Serial.print( netwTimer/1000L );
	Serial.print(F(", busy=")); Serial.print(  timers3[NW_TIMER_BUSY]/1000  );
//
	Serial.print(F(", eolCnt=")); Serial.print( eolCount );
	Serial.print(F(", payLin=")); Serial.print( payLin );
	Serial.print(F(", payLout=")); Serial.print( payLout );
	Serial.print(F(", empty=")); Serial.print( empty );

////	Serial.print(F(", pLoad>"));
////	for(int i=payLout;i!=payLin;i++)
////	{
////		i = i % PAYLOAD_LENGTH;
////		Serial.print((char)payLoad[i]);
////	}
////	Serial.print(F("<"));
//
	Serial.print(F(", rx=")); Serial.print( rxBufIn );
	Serial.print(F("-")); Serial.print( rxBufOut );
	Serial.print(F("-")); Serial.print( rxFiFo[rxBufOut].timestamp>0 );
 

	Serial.print(F(", tx=")); Serial.print( txBufIn );
	Serial.print(F("-")); Serial.print( txBufOut );
	Serial.print(F("-")); Serial.print( txFiFo[txBufOut].timestamp>0 );
	Serial.print(F(" cnt=")); Serial.print( sendCount );
////	Serial.print(F(" err=")); Serial.print( sendErrorCount );
////	Serial.print(F(" rtry=")); Serial.print( sendRetryCount );
//
	Serial.println();
	Serial.flush();
}


