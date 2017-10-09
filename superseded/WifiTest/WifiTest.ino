#include <SoftwareSerial.h>
//#include <string.h>
#define TIMEOUT 5000 // mS
#define LED 5

#define encoderButtonPin A3    // the number of the pushbutton pin
#define LCDBacklightOnPin 13 //via TIP120 darlington

#define SSID "ford_prefect_2.4"
#define PASS "annabanana"
#define IP "184.106.153.149" // thingspeak.com
String GET = "GET /update?key=WTYK34F502K75NFE";

SoftwareSerial mySerial(A5, A4); // RX, TX


//Switch Variables
int encoderButtonState = LOW;
int lastEncoderButtonState = LOW;
long time = 0;
long debounce = 200;


void setup()
{
  pinMode(LCDBacklightOnPin, OUTPUT);
  digitalWrite(LCDBacklightOnPin, LOW);
  pinMode(encoderButtonPin, INPUT);


  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Ready to go");
  SendCommand("AT+RST", "Ready");
  delay(5000);
  SendCommand("AT+CWMODE=1", "OK");
  SendCommand("AT+CIFSR", "OK");
  SendCommand("AT+CIPMUX=1", "OK");
  SendCommand("AT+CIPSERVER=1,80", "OK");
}

void loop() {
  /*if (mySerial.available())
    Serial.write(mySerial.read());
    if (Serial.available())
    mySerial.write(Serial.read());*/

  encoderButtonState = digitalRead(encoderButtonPin);

  if (encoderButtonState == HIGH) {
    /*mySerial.println("AT+CIPSEND=0,28");
      mySerial.println("<h1>Button was pressed!</h1>");
      delay(1000);
      SendCommand("AT+CIPCLOSE=0","OK");*/
    Serial.println("Button Pressed");
    updateTemp("0", "20", "22", "21",
               "0", "False", "False");
  }

  /******************************/
  //Buttons
  /*if (encoderButtonState == HIGH && encoderButtonState != lastEncoderButtonState) {
    digitalWrite(LCDBacklightOnPin, HIGH);
    Serial.println("on");
    encoder0Pos = knob.read();
    } else if (encoderButtonState == LOW && encoderButtonState != lastEncoderButtonState) {
    digitalWrite(LCDBacklightOnPin, LOW);
    Serial.println("off");
    }*/

  /******************************/

  String IncomingString = "";
  boolean StringReady = false;

  while (mySerial.available()) {
    IncomingString = mySerial.readString();
    StringReady = true;

  }

  if (StringReady) {
    //Serial.println("Received String: " + IncomingString);

    if (IncomingString.indexOf("LED=ON") != -1) {
      digitalWrite(LCDBacklightOnPin, HIGH);
      Serial.println("LED=ON");
    }

    if (IncomingString.indexOf("LED=OFF") != -1) {
      digitalWrite(LCDBacklightOnPin, LOW);
      Serial.println("LED=OFF");
    }

  }

}

boolean SendCommand(String cmd, String ack) {
  mySerial.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack)) // timed out waiting for ack string
    return true; // ack blank or ack found
}

boolean echoFind(String keyword) {
  byte current_char = 0;
  byte keyword_length = keyword.length();
  long deadline = millis() + TIMEOUT;
  while (millis() < deadline) {
    if (mySerial.available()) {
      char ch = mySerial.read();
      Serial.write(ch);
      if (ch == keyword[current_char])
        if (++current_char == keyword_length) {
          Serial.println();
          return true;

        }

    }

  }
  return false; // Timed out
}

void updateTemp(String tenmp1, String temp2, String tempAvg,
                String tempInternal, String heaterOn, String compressorOn) {

  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";

  Serial.println(cmd);
  mySerial.println(cmd);
  delay(2000);
  if (mySerial.find("Error")) {
    Serial.println("Error");
    return;
  }
  cmd = GET;
  cmd += "&field1=";
  cmd += currenttime;
  cmd += "&field2=";
  cmd += tenmp1;
  cmd += "&field3=";
  cmd += temp2;
  cmd += "&field4=";
  cmd += tempAvg;
  cmd += "&field5=";
  cmd += tempInternal;
  cmd += "&field6=";
  cmd += heaterOn;
  cmd += "&field7=";
  cmd += compressorOn;
  cmd += "\r\n";
  mySerial.print("AT+CIPSEND=");
  mySerial.println(cmd.length());
  mySerial.print(cmd);
  Serial.println(cmd);
  mySerial.println("AT+CIPCLOSE");

}


