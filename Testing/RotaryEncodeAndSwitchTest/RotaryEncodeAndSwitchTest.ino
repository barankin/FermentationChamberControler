/*
  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 7
   LCD D5 pin to digital pin 6
   LCD D6 pin to digital pin 5
   LCD D7 pin to digital pin 4
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Encoder.h>

//rotary encoder pins
#define Rotary_Encoder_Pin_A 8
#define Rotary_Encoder_Pin_B 3
#define encoderButtonPin A3    // the number of the pushbutton pin

#define LCDBacklightOnPin 13 //via TIP120 darlington

//Switch Variables
int encoderButtonState = LOW;
int reading;
int previous = HIGH;
int lastEncoderButtonState = LOW;
long time = 0;
long debounce = 200;

//Encoder Variables
long encoder0Pos = 0;

//Temperature Value
const float defaultSetTemp = 20.0f;
float setTempC = defaultSetTemp;
float maxTempC = 30.0f, minTempC = 2.0f;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
Encoder knob(Rotary_Encoder_Pin_B, Rotary_Encoder_Pin_A);

void setup() {
  pinMode(LCDBacklightOnPin, OUTPUT);
  digitalWrite(LCDBacklightOnPin, LOW);
  pinMode(encoderButtonPin, INPUT);
  digitalWrite(LCDBacklightOnPin, LOW);
  Serial.begin(9600);
  Serial.println("Serial is working");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Set ");lcd.print((char)223);lcd.print("C:");
  lcd.setCursor(8, 0);
  lcd.print(setTempC);
  Serial.println(setTempC);
}

void loop() {
  reading = digitalRead(encoderButtonPin);
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (encoderButtonState == HIGH)
      encoderButtonState = LOW;
    else
      encoderButtonState = HIGH;

    time = millis();
  }
  previous = reading;

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  if (encoderButtonState == HIGH && encoderButtonState != lastEncoderButtonState) {
    digitalWrite(LCDBacklightOnPin, HIGH);
    Serial.println("on");
    encoder0Pos = knob.read();
  } else if (encoderButtonState == LOW && encoderButtonState != lastEncoderButtonState) {
    digitalWrite(LCDBacklightOnPin, LOW);
    Serial.println("off");
  }
  if (encoderButtonState == HIGH) {
    long newPosition;
    newPosition = knob.read();
    if (newPosition != encoder0Pos) {
      float positionDifference = newPosition - encoder0Pos;
      encoder0Pos = newPosition;
      setTempC += positionDifference / 50;
      Serial.println(setTempC);

      lcd.setCursor(8, 0);
      lcd.print(setTempC);
    }
  }
  lastEncoderButtonState = encoderButtonState;
}

