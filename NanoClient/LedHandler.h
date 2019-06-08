int ledColor[3];

void LedHandlerSetup();
void LedHandlerLoop();
void setLedColor(char*);
void pushLedColor(char*);

void LedHandlerSetup(){
	ledColor[COLOR_R] = LED_COLOR_DEFAULT_R;
	ledColor[COLOR_G] = LED_COLOR_DEFAULT_G;
	ledColor[COLOR_B] = LED_COLOR_DEFAULT_B;
	
	pinMode(R_LED_PIN, OUTPUT);
	pinMode(G_LED_PIN, OUTPUT);
	pinMode(B_LED_PIN, OUTPUT);
}

void LedHandlerLoop(){
	#if DEBUG
	Serial.print("LedManager      --> Color(R:");
	Serial.print(ledColor[COLOR_R]);
	Serial.print(" G: ");
	Serial.print(ledColor[COLOR_G]);
	Serial.print(" B: ");
	Serial.print(ledColor[COLOR_B]);
	Serial.println(")");
	#endif
  
	long currentTimeStamp = timeSet[HOURS] * 60 * 60 + timeSet[MINUTES] * 60 + timeSet[SECONDS];
	long alarmTimeStamp = alarmTimeSet[HOURS] * 60 * 60 + alarmTimeSet[MINUTES] * 60 + alarmTimeSet[SECONDS];
	long difference = alarmTimeStamp - currentTimeStamp;
  
	if(alarmStatus == 1){
		double rate = 0.0;
		if(difference <= alarmTimeInterval)
			rate = 1.0 - difference / (double)alarmTimeInterval;
		int r = (int)(ledColor[COLOR_R] * rate);
		int g = (int)(ledColor[COLOR_G] * rate);
		int b = (int)(ledColor[COLOR_B] * rate);
		if(r > 254)
			r = 254;
		if(g > 254)
			g = 254;
		if(b > 254)
			b = 254;
		analogWrite(R_LED_PIN, r);
		analogWrite(G_LED_PIN, g);
		analogWrite(B_LED_PIN, b);
	}else{
		analogWrite(R_LED_PIN, ledColor[COLOR_R] * 0);
		analogWrite(G_LED_PIN, ledColor[COLOR_G] * 0);
		analogWrite(B_LED_PIN, ledColor[COLOR_B] * 0);
	}
}

void setLedColor(char* ptr){
	setIntArray(ptr, &ledColor[0]);
}

void pushLedColor(char* outBuffer){
	pushInt(outBuffer, ledColor[COLOR_R]);
	pushChar(outBuffer, '.');
	pushInt(outBuffer, ledColor[COLOR_G]);
	pushChar(outBuffer, '.');
	pushInt(outBuffer, ledColor[COLOR_B]);
	pushChar(outBuffer, '!');
}