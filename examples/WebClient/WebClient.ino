
#include "flprogWiFi.h"


FLProgOnBoardWifi WifiInterface;


const char* host = "djxmmx.net";
const uint16_t port = 17;

void setup() {
  Serial.begin(115200);

  WifiInterface.clientOn();
  WifiInterface.setDhcp();
  WifiInterface.mac(0x78, 0xAC, 0xC0, 0x2C, 0x3E, 0x28); //--Установка MAC-адрес контроллера (лучше адрес прошитый производителем);
  WifiInterface.setClientSsidd("yana");
  WifiInterface.setClientPassword("12345678");


  while ( !WifiInterface.isReady()) {
    WifiInterface.pool();
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WifiInterface.localIP());
}

void loop() {

  static bool wait = false;

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  FLProgWiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    client.println("hello from ESP8266");
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  if (wait) {
    delay(300000);  // execute once every 5 minutes, don't flood remote service
  }
  wait = true;
}