#include "flprogWiFi.h"

FLProgOnBoardWifi WifiInterface;
FlprogWiFiServer wifiServer(&WifiInterface, 80);

bool isNeedSendConnectMessage = true;
bool isNeedSendDisconnectMessage = true;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Ожидаем инициализацию порта
  }
  Serial.println("Wifi WebServer демонстрация");
  if (WifiInterface.isImitation())
  {
    Serial.println("На этой плате нет встроеннного WiFi");
  }
  WifiInterface.apOn();
  WifiInterface.setApMac(0x78, 0xAC, 0xC0, 0x0D, 0x5B, 0x86);
  WifiInterface.setApSsid("testESP");
  WifiInterface.setApPassword("12345678");
  WifiInterface.setApIp(IPAddress(192, 168, 1, 1));
  WifiInterface.setApDns(IPAddress(192, 168, 1, 1));
  WifiInterface.setApSubnet(IPAddress(255, 255, 255, 0));
  WifiInterface.setApGateway(IPAddress(192, 168, 1, 1));

  WifiInterface.clientOn();
  WifiInterface.setClientDhcp();
  WifiInterface.setClientMac(0x78, 0xAC, 0xC0, 0x2C, 0x3E, 0x28);
  WifiInterface.setClientSsidd("totuin-router");
  WifiInterface.setClientPassword("12345678");
  /*

    WifiInterface.setClientIp(192, 168, 199, 55);
    WifiInterface.setClientDns(192, 168, 199, 1);
    WifiInterface.setClientSubnet(255, 255, 255, 0);
    WifiInterface.setClientGateway(192, 168, 199, 1);
  */
}

void loop()
{
  WifiInterface.pool();
  if (WifiInterface.getClientStatus())
  {
    if (isNeedSendConnectMessage)
    {
      Serial.println("WiFi клиент подключён!");
      Serial.print("Ip - ");
      Serial.println(WifiInterface.localIP());
      Serial.print("Subnet mask - ");
      Serial.println(WifiInterface.subnetMask());
      Serial.print("Gateway IP - ");
      Serial.println(WifiInterface.gatewayIP());
      Serial.print("Dns IP - ");
      Serial.println(WifiInterface.dnsIP());
      isNeedSendConnectMessage = false;
      isNeedSendDisconnectMessage = true;
    }
  }
  else
  {
    if (isNeedSendDisconnectMessage)
    {
      Serial.println("WiFi клиент отключён!");
      isNeedSendConnectMessage = true;
      isNeedSendDisconnectMessage = false;
    }
  }

  FLProgWiFiClient wifiClient = wifiServer.accept();
  if (wifiClient)
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (wifiClient.connected())
    {
      if (wifiClient.available())
      {
        char c = wifiClient.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          // send a standard http response header
          wifiClient.println("HTTP/1.1 200 OK");
          wifiClient.println("Content-Type: text/html");
          wifiClient.println("Connection: close"); // the connection will be closed after completion of the response
          wifiClient.println("Refresh: 5");        // refresh the page automatically every 5 sec
          wifiClient.println();
          wifiClient.println("<!DOCTYPE HTML>");
          wifiClient.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++)
          {
            int sensorReading = analogRead(analogChannel);
            wifiClient.print("analog input ");
            wifiClient.print(analogChannel);
            wifiClient.print(" is ");
            wifiClient.print(sensorReading);
            wifiClient.println("<br />");
          }
          wifiClient.println("</html>");
          break;
        }
        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    // client.stop();
    Serial.println("client disconnected");
  }
  delay(500);
}