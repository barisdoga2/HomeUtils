int alarmTimeSet[3];
int alarmStatus;
int alarmTimeInterval;

void AlarmHandlerSetup();
void AlarmHandlerLoop();
void setAlarmTime(char*);
void setAlarmStatus(char*);
void setAlarmInterval(char*);
void pushAlarmTime(char*);
void pushAlarmStatus(char*);
void pushAlarmInterval(char*);

void AlarmHandlerSetup(){
	alarmTimeInterval = ALARM_TIME_INTERVAL_DEFAULT_SECONDS;
}

void AlarmHandlerLoop(){
	#if DEBUG
	Serial.print("AlarmManager    --> Status(");
	Serial.print(alarmStatus);
	Serial.print(") | Time(H:");
	Serial.print(alarmTimeSet[HOURS]);
	Serial.print(" M:");
	Serial.print(alarmTimeSet[MINUTES]);
	Serial.print(" S:");
	Serial.print(alarmTimeSet[SECONDS]);
	Serial.print(") | Interval(");
	Serial.print(alarmTimeInterval);
	Serial.println(")");
	#endif
}

void setAlarmTime(char* ptr){
	setIntArray(ptr, &alarmTimeSet[0]);
}

void setAlarmStatus(char* ptr){
	setInt(ptr, &alarmStatus);
}

void setAlarmInterval(char* ptr){
	setInt(ptr, &alarmTimeInterval);
}

void pushAlarmTime(char* outputBuffer){
	pushInt(outputBuffer, alarmTimeSet[HOURS]);
	pushChar(outputBuffer, '.');
	pushInt(outputBuffer, alarmTimeSet[MINUTES]);
	pushChar(outputBuffer, '.');
	pushInt(outputBuffer, alarmTimeSet[SECONDS]);
	pushChar(outputBuffer, '!');
}

void pushAlarmStatus(char* outputBuffer){
	pushInt(outputBuffer, alarmStatus);
	pushChar(outputBuffer, '!');
}

void pushAlarmInterval(char* outputBuffer){
	pushInt(outputBuffer, alarmTimeInterval);
	pushChar(outputBuffer, '!');
}