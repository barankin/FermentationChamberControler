#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID        "ford_prefect_2.4"
#define PASSWORD    "annabanana"
#define HOST_NAME "api.thingspeak.com"
#define KEY "WTYK34F502K75NFE"
#define HOST_PORT (80)

SoftwareSerial mySerial(A5, A4); /* RX:D3, TX:D2 */
ESP8266 wifi(mySerial);

void setupWIFI(void);
void postSensorData(String temp1, String temp2, String tempAvg,
                    String tempInternal, String heaterOn, String compressorOn);

void setup() {
  Serial.begin(9600);
  Serial.println("Start!");

  setupWIFI();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop start");
  delay(3000);
  postSensorData("20", "22", "21",  "0", "0", "0");
}

void setupWIFI() {

  Serial.print("WIFI setup begin\r\n");
  wifi.restart();
  delay(2000);

  /*
    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());

    Serial.print(wifi.getAPList().c_str());

    Serial.print("IP Address: ");
    Serial.println(wifi.getLocalIP().c_str());

    Serial.print("IP Status: ");
    Serial.println(wifi.getIPStatus().c_str());
  */

  if (wifi.setOprToStation()) {
    Serial.print("to station ok\r\n");
  } else {
    Serial.print("to station err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }
  wifi.disableMUX();
  Serial.print("WIFI setup end\r\n");

}

void postSensorData(String temp1, String temp2, String tempAvg,
                    String tempInternal, String heaterOn, String compressorOn) {
  //Serial.println("Debug 1");
  uint8_t buffer[1024] = {0};
  //Serial.println("Debug 2");
  //delay(500);
  
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print("create tcp ok\r\n");
  } else {
    Serial.print("create tcp err\r\n");
    return;
  }

  String http = String();
  http += "GET /update?key=";
  http += KEY;
  http += "&field1=" + temp1;
  http += "&field2=" + temp2;
  http += "&field3=" + tempAvg;
  http += "&field4=" + tempInternal;
  http += "&field5=" + heaterOn;
  http += "&field6=" + compressorOn;
  http += " HTTP/1.1\r\n";
  http += "Host: api.thingspeak.com\r\n";
  http += "Connection: close\r\n\r\n";

  Serial.println(http);
  wifi.send((const uint8_t*)http.c_str(), http.length());

  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
    Serial.print("Received:[");
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
  }

  if (wifi.releaseTCP()) {
    Serial.print("release tcp ok\r\n");
  } else {
    Serial.print("release tcp err\r\n");
  }
}

