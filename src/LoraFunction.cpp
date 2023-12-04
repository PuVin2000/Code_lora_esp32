#include <Arduino.h>

#include "include.h"

float Humid1;
float Temp1;
bool CheckMessage1;

void setupLora()
{
  Serial.println("LoRa Master Node");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  // LoRa.onReceive(onReceive);
  // LoRa.receive();
  // while (true)
  // {
  //   rtc_wdt_feed();
  //   vTaskDelay(pdMS_TO_TICKS(100));
  // }
}

void sendMessage(String outgoing, byte CenterNode, byte otherNode)
{
  LoRa.beginPacket();            // start packet
  LoRa.write(otherNode);         // add destination address
  LoRa.write(CenterNode);        // add sender address
  LoRa.write(msgCount);          // add message ID
  LoRa.write(outgoing.length()); // add payload length
  LoRa.print(outgoing);          // add payload
  LoRa.endPacket();              // finish packet and send it
  msgCount++;                    // increment message ID
}
void onReceive(int packetSize)
{
  if (packetSize == 0)
    return; // if there's no packet, return
  // read packet header bytes:
  int recipient = LoRa.read(); // recipient address
  byte sender = LoRa.read();   // sender address
  if (sender == 0XBB)
    SenderNode = "Node1:";
  if (sender == 0XCC)
    SenderNode = "Node2:";
  byte incomingMsgId = LoRa.read();  // incoming msg ID
  byte incomingLength = LoRa.read(); // incoming msg length

  char incoming[256];

  for (int i = 0; i < packetSize; i++)
  {
    incoming[i] = (char)LoRa.read();
  }
  incoming[packetSize] = '\0';

  if (recipient != Node1 && recipient != MasterNode)
  {
    // Serial.println("This message is not for me.");
    ;
    return; // skip rest of function
  }
  if (sender == 0XBB)
  {
    CheckMessage1 = true;
    GetHuMid1 = getValue(incoming, ',', 0); // Soil Moisture Value
    Humid1 = GetHuMid1.toFloat();

    GetTemp1 = getValue(incoming, ',', 1); // Temp Moisture Value
    Temp1 = GetTemp1.toFloat();
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
/*
    String v = getValue(incoming, ',', 0); // Soil Moisture Value
    soilMoistureValue = v.toInt();
    Serial.println("hello2345");
    Serial.println(soilMoistureValue);
    Serial.println(esp_get_free_heap_size());
    Serial.println(esp_get_minimum_free_heap_size());
    Firebase.setInt(Firebase_DATA1, "/IOT/Humid", soilMoistureValue);
*/