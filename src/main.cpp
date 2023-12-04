#include <Arduino.h>

#include "include.h"


void sendDataToFireBase();
unsigned long time_1;

void setup()
{
  Serial.begin(9600); // initialize serial
  while (!Serial)
    ;
  setup_Firebase();
  setupLora();
}
void loop()
{
  // Serial.println("1");
  sendDataToFireBase();
  if ((unsigned long)(millis() - time_1) > 2000)
  {
    time_1 = millis();
    //Firebase.setInt(Firebase_DATA1, "/IOT/Humid", random(2, 10));
    //sendMessage("0",MasterNode,Node1);
  }
  onReceive(LoRa.parsePacket());
  Serial.println(1);
}

void sendDataToFireBase(){
  if (CheckMessage1 == 1)
    {
      Serial.println(Humid1);
      Serial.println(456);
      Firebase.setFloat(Firebase_DATA1, "/IOT/Area1/Humid", Humid1);
      Firebase.setFloat(Firebase_DATA1, "/IOT/Area1/Temp", Temp1);
    }
    CheckMessage1 = 0;
}

