#include <Arduino.h>

#include "include.h"


// cài đặt PWM
int Value_PWM = 0;

void setup_Firebase()
{
  // put your setup code here, to run once:
  WiFi_Config();
  Firebase_Config();
  //PWM_Config();
  if (!Firebase.beginStream(Lighting_Value, "/IOT/Light"))
  {
    // Could not begin stream connection, then print out the error detail
    Serial.println(Lighting_Value.errorReason());
  }
  Firebase.setStreamCallback(Lighting_Value, streamCallback, streamTimeoutCallback);
}

void streamCallback(StreamData data)
{

  // Print out all information

  Serial.println("Stream Data...");
  Serial.println(data.streamPath());
  Serial.println(data.dataPath());
  Serial.println(data.dataType());

  // Print out the value
  // Stream data can be many types which can be determined from function dataType

  if (data.dataTypeEnum() == fb_esp_rtdb_data_type_integer)
    Serial.println(data.to<int>());
  else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_float)
    Serial.println(data.to<float>(), 5);
  else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_double)
    printf("%.9lf\n", data.to<double>());
  else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_boolean)
    Serial.println(data.to<bool>() ? "true" : "false");
  else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_string)
    Serial.println(data.to<String>());
  else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_json)
  {
    FirebaseJson *json = data.to<FirebaseJson *>();
    Serial.println(json->raw());
  }
  else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_array)
  {
    FirebaseJsonArray *arr = data.to<FirebaseJsonArray *>();
    Serial.println(arr->raw());
  }

  if (data.streamPath() == "/IOT/Light")
  {
    String data_getString = data.to<String>();
    Serial.println(1);
    sendMessage(data_getString, MasterNode, Node1);
  }
}


void streamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    // Stream timeout occurred
    Serial.println("Stream timeout, resume streaming...");
  }
}

void WiFi_Config()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {

    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connecting with IP:");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void Firebase_Config()
{
  // connect Firebase-----------
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void PWM_Config()
{

  // setup kênh pwm
  ledcSetup(ledChannel, freq, resolution);

  // xuất pwm ra chân 16
  ledcAttachPin(ledPin, ledChannel);
}
