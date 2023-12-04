#include <FirebaseESP32.h>

#define WIFI_NAME "Mi phone"
#define WIFI_PASSWORD "0984647944" 

#define FIREBASE_HOST "da2-songnganh-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "IHiS7PEKiGM7ZuQ2gjvwc6XItORKOtFQJK0duLz3"

#define LED 2


void setup_Firebase();
void streamCallback(StreamData data);
void streamTimeoutCallback(bool timeout);
void WiFi_Config();
void Firebase_Config();
void PWM_Config();

void update_Humid(int *pHumid);


