void setupLora();
void onReceive(int packetSize);
String getValue(String data, char separator, int index);
void sendMessage(String outgoing, byte CenterNode, byte otherNode);
//void update_Humid();
void TaskupDateFB( void *pvParameters);