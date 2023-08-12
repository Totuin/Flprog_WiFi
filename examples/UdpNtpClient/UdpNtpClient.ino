//=================================================================================================
//                              1.Test Ethernet
//  Получение по UDP точного времени.
//=================================================================================================
#include "flprogWiFi.h" //подключаем библиотеку Wifi

//=================================================================================================
//  Определяем целевую платформу
//=================================================================================================

#ifdef ARDUINO_ARCH_AVR
#define TEST_BOARD "AVR"
#elif ARDUINO_ARCH_SAM
#define TEST_BOARD "SAM"
#elif ARDUINO_ARCH_ESP8266
#define TEST_BOARD "ESP8266"
#elif ARDUINO_ARCH_ESP32
#define TEST_BOARD "ESP32"
#elif ARDUINO_ARCH_RP2040
#define TEST_BOARD "RP2040"
#elif ARDUINO_ARCH_STM32
#define TEST_BOARD "STM32"
#else
#define TEST_BOARD "ANON"
#endif

//-------------------------------------------------------------------------------------------------
//       Создание интерфейса WiFi
//-------------------------------------------------------------------------------------------------
FLProgOnBoardWifi WifiInterface;

//-------------------------------------------------------------------------------------------------
//         Задание параметров интернет соеденения и параметров UDP
//-------------------------------------------------------------------------------------------------

uint32_t localPort = 8888;                            //--Определение порта для UDP пакетов (используется стандартный номер);
const char timeServer[] = "time.nist.gov";            //--Имя NTP сервера - сервер точного времени;
const int NTP_PACKET_SIZE = 48;                       //--Установка размера буфера (отметка времени NTP находится в первых 48 байтах сообщения);
uint8_t packetBuffer[NTP_PACKET_SIZE];                //--Создание буфера для хранения входящих и исходящих пакетов;
uint16_t cntGettingNTP = 0;                           //--Cчетчик принятых пакетов;
bool isNeedSendConnectMessage = true;
bool isNeedSendDisconnectMessage = true;

//-------------------------------------------------------------------------------------------------
//          1.2.Создание объекта UDP для отправки и получения пакетов по UDP с привязкой к интерфейсу
//-------------------------------------------------------------------------------------------------
FLProgWiFiUDP Udp(&WifiInterface); //--Создание UDP клиента;

//-----------------------------------------------------------------------------------------
//          1.3.Определение рабочих параметров и функций
//-----------------------------------------------------------------------------------------
uint32_t  sendPacadeTime;   // Время начала ожидания
uint32_t reqestPeriod = 5000;         // Периодичность запроса времени от сервера
bool isReplyInProcess = false;        // Флаг ожидания ответа

void sendNTPpacket(const char *nameSever); //--Предопределение функции;
void processingResponse();                 //--Предопределение функции;

//=================================================================================================
void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }
  Serial.print(String(F("\n-----Тест UdpNtpClient для платы ")));
  Serial.print(String(F(TEST_BOARD)));
  Serial.println(String(F("-----")));
  if (WifiInterface.isImitation())
  {
    Serial.println("На этой плате нет встроеннного WiFi");
  }

  WifiInterface.clientOn();
  WifiInterface.setClientDhcp();
  WifiInterface.setClientMac(0x78, 0xAC, 0xC0, 0x2C, 0x3E, 0x28); //--Установка MAC-адрес контроллера (лучше адрес прошитый производителем);
  WifiInterface.setClientSsidd("totuin-router");
  WifiInterface.setClientPassword("12345678");

  sendPacadeTime = flprog::timeBack(reqestPeriod);
}
//=================================================================================================
void loop()
{
  WifiInterface.pool(); // Цикл работы интерфейса
  //-------------------------------------------------------------------------------------------------
  //                                           Основная логика
  //-------------------------------------------------------------------------------------------------
  if ( WifiInterface.getClientStatus())
  {
    if (isNeedSendConnectMessage)
    {
      //-------------------------------------------------------------------------------------------------
      //                      Если интерфейс готов то вывод сообщения о подключении
      //-------------------------------------------------------------------------------------------------
      Serial.println("WiFi клиент подключён!");
      Serial.print("Ip - ");
      Serial.println(WifiInterface.localIP());
      isNeedSendConnectMessage = false;
      isNeedSendDisconnectMessage = true;
    }
    //-------------------------------------------------------------------------------------------------
    //                          работаем с NTP сервером
    //-------------------------------------------------------------------------------------------------
    if (isReplyInProcess)
    {
      //--Если  ждём ответа проверяем ответ
      processingResponse();
    }
    else
    {
      //--Если не ждём ответа отправляем запрос
      sendNTPpacket(timeServer);
    }
  }
  else
  {
    //-------------------------------------------------------------------------------------------------
    //      Если интерфейс не готов то  выводим один раз сообщение об обрыве связи
    //-------------------------------------------------------------------------------------------------
    if (isNeedSendDisconnectMessage)
    {
      Serial.println("WiFi клиент отключён!");
      isNeedSendConnectMessage = true;
      isNeedSendDisconnectMessage = false;
    }
  }

} //======END loop();

// #################################################################################################
//=================================================================================================
//                         1.ФУНКЦИЯ sendNTPpacket(*nameServer)
//     Формирование запроса в буфере packetBuffer и его отправка в NTP сервер
//=================================================================================================
void sendNTPpacket(const char *nameServer)
{
  //-------------------------------------------------------------------------------------------------
  //                 Отправка запроса на сервер точного времени
  //------------------------------------------------------------------------------------------------ -
  if (!flprog::isTimer(sendPacadeTime, reqestPeriod)) //--Проверяем - прошло ли время после последнего запроса
  {
    return; //-- Если нет - выходим
  }

  if (WifiInterface.isBusy()) //--Проверяем готов ли и не занят ли интерфейс
  {
    return; //--Если не готов или занят - выходим
  }
  //-------------------------------------------------------------------------------------------------
  //  1.1.Инициализация буфера для отправки запросра требуемой формы в  NTP сервер
  //    (see URL above for details on the packets)
  //    Байты 4-11: 8 bytes of zero for Root Delay & Root Dispersion
  //-------------------------------------------------------------------------------------------------
  Udp.begin(localPort);
  memset(packetBuffer, 0, NTP_PACKET_SIZE); //--Очистка буфера
  packetBuffer[0] = 0b11100011;             // LI, Version, Mode
  packetBuffer[1] = 0;                      // Stratum, or type of clock
  packetBuffer[2] = 6;                      // Polling Interval
  packetBuffer[3] = 0xEC;                   // Peer Clock Precision
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  //-------------------------------------------------------------------------------------------------
  //   1.2.Отправка подготовленного  пакет с запросом метки времени
  //-------------------------------------------------------------------------------------------------
  Udp.beginPacket(nameServer, 123);         //--Инициализация NTP запроса к порту 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE); //--Отправка запроса;
  Udp.endPacket();                          //--Завершение запроса;
  WifiInterface.setBusy(); //--Занимаем интерфейс
  isReplyInProcess = true;   //--Вешаем флаг ожидания ответа

  sendPacadeTime = millis(); // --Запоминаем время отправки запроса
};                           //======END sendNTPpacket();

// #################################################################################################
//=================================================================================================
//                2.ФУНКЦИЯ processingResponse()
//                обработка ответа из NTP сервера
//=================================================================================================
void processingResponse()
{
  //-------------------------------------------------------------------------------------------------
  //                Ожидание ответа и его обработка
  //-------------------------------------------------------------------------------------------------
  if (!flprog::isTimer(sendPacadeTime, 1000)) // проверяем прошло ли время ожидания ответа
  {
    return; //-- если нет - выходим
  }
  isReplyInProcess = false;    // сбрасываем флаг ожидания ответа
  WifiInterface.resetBusy(); // освобождаем интерфейс

  //--Проверка наличия ответного пакета от сервера;
  if (!Udp.parsePacket())
  {
    return; //--если нет ответа - выходим
  }

  Udp.read(packetBuffer, NTP_PACKET_SIZE); //--Чтение пакета в буфер.read. В байтах 40-43 находятся сведения о времени;
  cntGettingNTP++;                         //--Считаем пакеты

  //--Вывод текущего, абсолютного и UNIX времени;
  uint16_t highWord = word(packetBuffer[40], packetBuffer[41]);
  uint16_t lowWord = word(packetBuffer[42], packetBuffer[43]);
  uint32_t secsSince1900 = ((uint32_t)highWord << 16) | lowWord; //--Получения времени в сек от 01.01.1900;

  //-------------------------------------------------------------------------------------------------
  //              Unix-time время в сек от 01.01.1970,
  //                  что соответствует 2208988800;
  //-------------------------------------------------------------------------------------------------
  uint32_t epoch = secsSince1900 - 2208988800UL;
  uint32_t vr;
  Serial.print(F("\nUTC(Greenwich)="));
  vr = (epoch % 86400L) / 3600;
  if (vr < 10)
  {
    Serial.print('0');
  }
  Serial.print(vr); //--Вывод часов (86400 сек в сутках);
  vr = (epoch % 3600) / 60;
  Serial.print(':');
  if (vr < 10)
  {
    Serial.print('0');
  }
  Serial.print(vr); //--Вывод минут (3600 сек в минуте);
  vr = epoch % 60;
  Serial.print(':');
  if (vr < 10)
  {
    Serial.print('0');
  }
  Serial.print(vr); //--Вывод сек;
  Serial.print(F(";  Time 01.01.1900="));
  Serial.print(secsSince1900); //--Вывод абсолютного времени в сек(с 01.01.1990);
  Serial.print(F(";  Time Unix="));
  Serial.print(epoch); //--Вывод UNIX времени (с 01.01.1970)
  Serial.print(F(";  Счетчик="));
  Serial.print(cntGettingNTP);
  Serial.println(';'); //--Вывод счетчика принятых пакетов;
};