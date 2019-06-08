#include <Wire.h>

int outBufferLength;
char outBuffer[I2C_BUFFER_SIZE] = "";
char inputBuffer[I2C_INPUT_BUFFER_MAX_LENGTH] = "";
int inLength = 0;

void I2CComSetup();
void I2CComLoop();
void receiveEvent(int);
void requestEvent();

void I2CComSetup(){
	Wire.begin(8);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
}

void I2CComLoop(){
	// NOT TO DO
}

void receiveEvent(int howMany) {
	while(Wire.available()){
		char c = Wire.read();
		inputBuffer[inLength] = c;
		inLength++;
	}
  
	if(inputBuffer[inLength - 1] == PACKET_END_IDENTIFIER){
		inputBuffer[inLength] = '\0'; 
		char* rest = inputBuffer;
		char* ptr;
		ptr = strtok_r(rest, "#", &rest);
		while(ptr != NULL){
			// ClockHandler
			if(strncmp(ptr, TIME_SET, 2) == 0){
				setTime(ptr);
			}else if(strncmp(ptr, TIME_SET_REQUEST, 2) == 0){
				pushTime(outBuffer);
			}else if(strncmp(ptr, TIME_IS_SET_REQUEST, 2) == 0){
				pushIsTime(outBuffer);
			}
			
			// SensorHandler
			else if(strncmp(ptr, SENSOR_INTERVAL_SET, 2) == 0){
				setSensorIntervalSeconds(ptr);
			}else if(strncmp(ptr, SENSOR_TEMPERATURE_REQUEST, 2) == 0){
				pushTemperature(outBuffer);
			}else if(strncmp(ptr, SENSOR_HUMIDITY_REQUEST, 2) == 0){
				pushHumidity(outBuffer);
			}else if(strncmp(ptr, SENSOR_INTERVAL_REQUEST, 2) == 0){
				pushSensorInterval(outBuffer);
			}else if(strncmp(ptr, SENSOR_CO2_REQUEST, 2) == 0){
        pushCO2(outBuffer);
      }
			
			// AlarmHandler
			else if(strncmp(ptr, ALARM_TIME_SET, 2) == 0){
				setAlarmTime(ptr);
			}else if(strncmp(ptr, ALARM_STATUS_SET, 2) == 0){
				setAlarmStatus(ptr);
			}else if(strncmp(ptr, ALARM_TIME_INTERVAL_SET, 2) == 0){
				setAlarmInterval(ptr);
			}else if(strncmp(ptr, ALARM_TIME_REQUEST, 2) == 0){
				pushAlarmTime(outBuffer);
			}else if(strncmp(ptr, ALARM_STATUS_REQUEST, 2) == 0){
				pushAlarmStatus(outBuffer);
			}else if(strncmp(ptr, ALARM_TIME_INTERVAL_REQUEST, 2) == 0){
				pushAlarmInterval(outBuffer);
			}
			
			// Led Handler
			else if(strncmp(ptr, LED_COLOR_SET, 2) == 0){
				setLedColor(ptr);
			}else if(strncmp(ptr, LED_COLOR_REQUEST, 2) == 0){
				pushLedColor(outBuffer);
			}
			
			ptr = strtok_r(NULL, "#", &rest);
		}
		
		inLength = 0;
	}
}

// Strictly Sends 32 bytes of data. No packing here.
void requestEvent() {
	Wire.write(outBuffer);
	outBuffer[0] = '\0';
	outBufferLength = 0;
}

