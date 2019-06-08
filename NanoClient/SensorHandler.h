#include <DHT.h>
#include "MQ135.h"
#define RZERO 206.85

DHT dht(DHT11_PIN, DHT11);
MQ135 gasSensor = MQ135(MQ135_PIN);

int sensorIntervalSeconds;
float temperature = 0;
float humidity = 0;
float co2 = 0;

void SensorHandlerSetup();
void SensorHandlerLoop();
void pushSensorInterval(char*);
void pushTemperature(char*);
void pushHumidity(char*);
void pushCO2(char*);
void setSensorIntervalSeconds(char*);
void sensorDataResponse();


void SensorHandlerSetup(){
	sensorIntervalSeconds = SENSOR_INTERVAL_DEFAULT_SECONDS;
  
	dht.begin();
	humidity = dht.readHumidity();
	temperature = dht.readTemperature();

  gasSensor.getRZero();
  co2 = gasSensor.getPPM();
  
}

void SensorHandlerLoop(){
	#if DEBUG
	Serial.print("SensorMaanger   --> Interval(");
	Serial.print(sensorIntervalSeconds);
	Serial.println(")");
	#endif
	
	humidity = dht.readHumidity();
	temperature = dht.readTemperature();
  co2 = gasSensor.getPPM();
  
}

void pushSensorInterval(char* outBuffer){
	pushInt(outBuffer, sensorIntervalSeconds);
	pushChar(outBuffer, '!');
}

void pushTemperature(char* outBuffer){
	pushFloat(outBuffer, temperature);
	pushChar(outBuffer, '!');
}

void pushHumidity(char* outBuffer){
	pushFloat(outBuffer, humidity);
	pushChar(outBuffer, '!');
}

void pushCO2(char* outBuffer){
  pushFloat(outBuffer, co2);
  pushChar(outBuffer, '!');
}

void setSensorIntervalSeconds(char* ptr){
	setInt(ptr, &sensorIntervalSeconds);
}

void sensorDataResponse(){
	#ifdef DEBUG
	Serial.println("SensorManager   --> INF= Sensor Data Request Arrived, Preparing Response!\n");
	#endif
}
