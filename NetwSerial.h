
#ifndef NETWSerial_H
#define NETWSerial_H

//#include "ArdUtils.h"
#include "NetwBase.h"

class NetwSerial : public NetwBase
{
public:

    int port=0;
    long baudRate=115200;
	#ifdef  __AVR_ATmega2560__
   		HardwareSerial* serialPtr;
	#endif


	virtual ~NetwSerial(){}  // suppress warning
	NetwSerial( )
	{
		// #ifndef  __AVR_ATmega2560__
		// 	serialPtr = &Serial;
		// #endif
	}

	void begin(void);
	void setup(void)
	{
		delay(4);
		// id=isParent?83:84;
	}

	void setup(int port, long baudrate)
	{
		// id=isParent?83:84;
		this->port = port;
		this->baudRate = baudrate;
		#ifndef  __AVR_ATmega2560__
			Serial.begin(baudrate);
			while(!Serial) {} // Wait
		#else
			if(port==0) { Serial.begin(baudrate);   serialPtr = &Serial;  while(!Serial){} }
			if(port==1) { Serial1.begin(baudrate);  serialPtr = &Serial1; while(!Serial1){} }
			if(port==2) { Serial2.begin(baudrate);  serialPtr = &Serial2; while(!Serial2){} }
			if(port==3) { Serial3.begin(baudrate);  serialPtr = &Serial3; while(!Serial3){} }
		#endif
	}

	void loop(void);


	int write( RxData *rxData);

    void trace(const char* id);

private:

};

#endif
