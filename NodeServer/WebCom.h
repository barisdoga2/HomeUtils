#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <string>

ESP8266WebServer webServer(80);

void handleRoot(){
  webServer.send(200, "text/plain", "/");
}

void handleReq(){
	String message = "";
	char setCommandBuff[WEB_SET_COMMAND_BUFFER_LENGTH];
  
   
	for (int i = 0; i < webServer.args(); i++) {
		String argN = webServer.argName(i);
		String argV = webServer.arg(i);
    char argVA[10];
		
		if(argN == GET_ARG){
			for(int k = 0 ; k < get_params_length ; k++){
				if(argV == get_params[k]){
          char getCommandBuff[10];
					sprintf(getCommandBuff,"%c%s%c",'#', get_params[k], '!');
					sendAndReceive(getCommandBuff);
					message += inputBuffer;
				}
			}
		}else{
			for(int k = 0 ; k < set_params_length ; k++){
				if(argN == set_params[k]){
					argV.toCharArray(argVA, argV.length() + 1);
					sprintf(setCommandBuff, "%s%c%s%c%s", setCommandBuff, '#', set_params[k], '=', argVA);
				}
			}
		}
	}
	sprintf(setCommandBuff, "%s%c", setCommandBuff, '!');
	sendAndReceive(setCommandBuff);
  
	webServer.send(200, "text/plain", message);       //Response to the HTTP request
}

void WebComSetup(){
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}

  webServer.on("/", handleRoot);
	webServer.on("/req", handleReq);

	webServer.begin();
}

void WebComLoop(){
	webServer.handleClient();
}

