int timeSet[3];
int isTimeSet;
unsigned long deltaTime;
long startTime;

void ClockHandlerSetup();
void ClockHandlerLoop();
void startClockTimer();
void stopClockTimer();
void pushTime(char*);
void pushIsTime(char*);
void setTime(char*);

void ClockHandlerSetup(){
	isTimeSet = 0;
	deltaTime = 0;
}

void ClockHandlerLoop(){
	if(deltaTime >= 1000){
		int secondsPass = deltaTime / 1000;
		deltaTime -= secondsPass * 1000;
		timeSet[SECONDS] += secondsPass;
		
		if(timeSet[SECONDS] >= 60){
			timeSet[MINUTES] += timeSet[SECONDS] / 60;
			timeSet[SECONDS] %= 60;
		}
		
		if(timeSet[MINUTES] >= 60){
			timeSet[HOURS] += timeSet[MINUTES] / 60;
			timeSet[MINUTES] %= 60;
		}
		
		if(timeSet[HOURS] >= 24){
			timeSet[HOURS] %= 24;
		}
	}
	#if DEBUG
	Serial.print("ClockManager    --> Set(");
	Serial.print(isTimeSet);
	Serial.print(") | Time(H:");
	Serial.print(timeSet[HOURS]);
	Serial.print(" M:");
	Serial.print(timeSet[MINUTES]);
	Serial.print(" S:");
	Serial.print(timeSet[SECONDS]);
	Serial.println(")");
	#endif
}

void startClockTimer(){
	startTime = millis();
	#if DEBUG
	Serial.println("------------------------------------------------------------------------------");
	#endif
}

void stopClockTimer(){
	deltaTime += millis() - startTime;
}

void pushTime(char* outputBuffer){
  int hms[3];
  hms[0] = timeSet[HOURS];
  hms[1] = timeSet[MINUTES];
  hms[2] = timeSet[SECONDS];
	pushInt(outputBuffer, hms[HOURS]);
	pushChar(outputBuffer, '.');
	pushInt(outputBuffer, hms[MINUTES]);
	pushChar(outputBuffer, '.');
	pushInt(outputBuffer, hms[SECONDS]);
	pushChar(outputBuffer, '!');
}

void pushIsTime(char* outBuffer){
	pushInt(outBuffer, isTimeSet);
	pushChar(outBuffer, '!');
}

void setTime(char* ptr){
	setIntArray(ptr, &timeSet[0]);
	isTimeSet = 1;
}

