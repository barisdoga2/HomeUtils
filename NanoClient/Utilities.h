void setIntArray(char*, int*);
void setInt(char*, int*);
void pushFloat(char*, float);
void pushInt(char*, int);
void pushCharArray(char*, char*);
void pushChar(char*, char);

void setIntArray(char* ptr, int* arr){
	char *tmp = strtok(ptr, "=");
	tmp = strtok(NULL, ".");
	int i = 0;
	for(i = 0; i <= sizeof(arr) / sizeof(int) + 1; i++){
		arr[i] = atoi(tmp);
		tmp = strtok(NULL, ".");
	}
}

void setInt(char* ptr, int* val){
	char *tmp = strtok(ptr, "=");
	tmp = strtok(NULL, ".");
	*val = atoi(tmp);
}

void pushFloat(char* ptr, float val){
	dtostrf(val, 1, 1, ptr + strlen(ptr));
}

void pushInt(char* ptr, int val){
	dtostrf(val, 1, 0, ptr + strlen(ptr));
}

void pushCharArray(char* ptr, char* arr){
	sprintf(ptr,"%s%s",ptr, arr);
}

void pushChar(char* ptr, char val){
	sprintf(ptr,"%s%c",ptr, val);
}

