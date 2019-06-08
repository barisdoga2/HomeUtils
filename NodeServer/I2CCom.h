#include <Wire.h>

char inputBuffer[I2C_BUFFER_SIZE];

void I2CComSetup();
void I2CComLoop();
void sendAndReceive(char[]);
void sendMsg(char*);
void receiveMsg();

void sendAndReceive(char* msg){
	sendMsg(msg);
	receiveMsg();
}

void sendMsg(char* msg){
	int msgLength = strlen(msg);
	char bf[I2C_BUFFER_SIZE] = "";
	int packetCount = ceil((double)msgLength / I2C_BUFFER_SIZE);
	
	int pckLen = 0;
	int pck = 0;
	for(pck = 0 ; pck < packetCount ; pck++){
		if((pck + 1) * I2C_BUFFER_SIZE <= msgLength){
			pckLen = I2C_BUFFER_SIZE;
		}else{
			pckLen = msgLength - pck * I2C_BUFFER_SIZE;
			bf[pckLen] = '\0';
		}
  
		memcpy(bf, msg + pck * I2C_BUFFER_SIZE * sizeof(char), pckLen);
		Wire.beginTransmission(8);
		Wire.write(bf);
		Wire.endTransmission();
		delay(20);
	}
}

// Strictly Receives 32 bytes of data. No packing here.
void receiveMsg(){
	Wire.requestFrom(8, I2C_BUFFER_SIZE);

	int inLng = 0;
	while(Wire.available() > 0){
		char inCh = Wire.read();
		inputBuffer[inLng++] = inCh; 
		if(inCh == '!'){
			inputBuffer[inLng] = '\0';
			while(Wire.available())
				Wire.read();
		}
	} 
}

void I2CComSetup(){
	Wire.begin(D1, D2);
}

void I2CComLoop(){
	// ** DO NOT CHANGE THIS COMMENT ** //
	// ** Nothing to implement here! ** //
}

