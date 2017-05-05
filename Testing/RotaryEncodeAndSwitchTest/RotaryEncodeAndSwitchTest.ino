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

//Switch Variables
int state = LOW;
int reading;
int previous = HIGH;
long time = 0;
long debounce = 200;

//Encoder Variables
long encoder0Pos = 0;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
Encoder knob(Rotary_Encoder_Pin_A, Rotary_Encoder_Pin_B);

void setup() {
  pinMode(encoderButtonPin, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.noDisplay();
  // Print a message to the LCD.
  lcd.print("hello, world!");
      lcd.setCursor(0,1);
    lcd.print(encoder0Pos);
}

void loop() {
    Serial.begin(9600);
    Serial.println("Serial is working");
  reading = digitalRead(encoderButtonPin);
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();
  }
  previous = reading;

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  if (state == HIGH) {
    lcd.display();
  } else {
    lcd.noDisplay();
  }

  long newPosition;
  newPosition = knob.read();
  if (newPosition != encoder0Pos) {
    float positionDifference = newPosition - encoder0Pos;
    Serial.println(positionDifference);
    encoder0Pos = newPosition;
    
    lcd.setCursor(0,1);
    lcd.print(encoder0Pos);
  }
}

