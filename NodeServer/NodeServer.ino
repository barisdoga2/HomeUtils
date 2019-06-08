#include "Map.h"
#include "I2CCom.h"
#include "WebCom.h"

void setup(void){
	Serial.begin(115200);
  
	I2CComSetup();
	WebComSetup();
}

void loop(void){
	I2CComLoop();
	WebComLoop();
}
