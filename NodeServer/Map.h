#define DEBUG 1

#define I2C_BUFFER_SIZE 32
#define WEB_SET_COMMAND_BUFFER_LENGTH 128

const char* WIFI_SSID = "SUPERONLINE_WiFi_4641";
const char* WIFI_PASSWORD = "AAUHMJEVXMU9";

#define GET_ARG "get"
const char * get_params[] = {
	"11",
    "12",
    
    "21",
    "22",
    "23",
    "24",

    "34",
    "35",
    "36",

    "41"
};
#define get_params_length (sizeof (get_params) / sizeof (const char *))

const char * set_params[] = {
    "10",
    
    "20",

    "31",
    "32",
    "33",

    "40"
};
#define set_params_length (sizeof (set_params) / sizeof (const char *))
