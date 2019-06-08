#include "Map.h"
#include "Utilities.h"
#include "ClockHandler.h"
#include "AlarmHandler.h"
#include "SensorHandler.h"
#include "LedHandler.h"
#include "I2CCom.h"

void setup(){
	Serial.begin(115200);
  Serial.println("On work!");
  
	ClockHandlerSetup();
	SensorHandlerSetup();
	AlarmHandlerSetup();
	LedHandlerSetup();
	I2CComSetup();
}

void softwareLoop(){
	ClockHandlerLoop();
	SensorHandlerLoop();
	AlarmHandlerLoop();
	LedHandlerLoop();
	I2CComLoop();
  
	delay(1000);
}

void loop(){
	startClockTimer();
	softwareLoop();
	stopClockTimer();
}

