#include <WiFi.h>
#include <FirebaseESP32.h>

#include <SPI.h>  // include libraries
#include <LoRa.h>
#include "soc/rtc_wdt.h"

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "LoraFunction.h"
#include "Firebase_function.h"

#define ss 5   // GPIO 5
#define rst 14 // GPIO 14
#define dio0 2 // GPIO 2

const int freq = 50;      // tần số xung
const int ledChannel = 0; // kênh PWM
const int resolution = 8; // độ phân giải 8bit
const int ledPin = 16;    // chọn chân 16 xuất tín hiệu


/* Lora_Config---------------------------------------------------- */
static byte MasterNode = 0x1F;
static byte Node1 = 0xBB;
static byte Node2 = 0xCC;

static String SenderNode = "";
static String outgoing;    // outgoing message
static byte msgCount = 0;  // count of outgoing messages
/* --------------------------------------------------------------- */

// khai báo static or const để không sinh lỗi multiple defination of
extern bool CheckMessage1;

static int soilMoistureValue;

const unsigned long previousMillis = 0;
const unsigned long int previoussecs = 0;
const unsigned long int currentsecs = 0;
const unsigned long currentMillis = 0;
const int interval = 1; // updated every 1 second
const int Secs = 0;

const int temperature = 0;
const int humidity = 0;
const int soilmoisturepercent = 0;

/// @brief Temp & Humid Area1
static String GetHuMid1;
extern float Humid1;

static String GetTemp1;
extern float Temp1;


static FirebaseData Firebase_DATA1;
static FirebaseData Firebase_DATA;
static FirebaseData Lighting_Value;

