
/* Fermentation Chamber Controller: arduino based fermentation chamber temperature controller
    stage one including:
    - Arduino Uno clone
    - lcd display
    - rotary encoder for changing temperature
    - two temperature probes DS18B20 using one wire bus
    - relay for turning compressor on and off
    - relay for turning heater on and off
    --
    stage two including:
    - logging using ESP-01 and Ai Thinker commands over hardware serial
    stage three including:
    - full control and status via ESP-01

   The LCD circuit for the LCD HelloWorld. We will use the same pin configuration:
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

/*
 * ToDo:
 * 1. modify set temperature with rotary encoder
 */
//-------------------------------------------------------------------------------------------//
#include <OneWire.h>            //to enable the DS18B20s
#include <DallasTemperature.h>  //to manipulate the DS18B20s
#include <LiquidCrystal.h>      //to set up the LCD
#include <EEPROM.h>             //to retrieve/save last set temperature
#include <Encoder.h>            //to facilitate the reading of the rotary encoder

//-------------------------------------------------------------------------------------------//

/* function declaration */
void setupDS18B20();
void setupFan();
void calcFanRPM(unsigned long currentMillis);
void rpm ();
void retrieveLastSetTemperaure();
void turnFanOn(int PWMValue);
void turnFanOff();
void updateLCDDisplay();

//-------------------------------------------------------------------------------------------//
// #define constants
//temperature sensor pins
#define ONE_WIRE_BUS 10
#define fanOnPin A0

//fan pin
#define fanSpeedPin 9 //pwm pin
#define fanSpeedSensor 3 //interupt pin for tracking fan RPM

//relay pins
#define Heater_Relay A2
#define Compressor_Relay A1

//rotary encoder pins
#define Rotary_Encoder_Pin_A 2
#define Rotary_Encoder_Pin_B 8
#define encoderButtonPin A3    // the number of the pushbutton pin

//LCD pins
#define LCD_RS 12
#define LCD_Enable 11
#define LCD_D4 7
#define LCD_D5 6
#define LCD_D6 5
#define LCD_D7 4

//eeprom address
#define SetTemperatureAddress 0

//other definitions
#define TEMPERATURE_PRECISION 11    //11=.0125C, 375ms used to select less precise temperature

//-------------------------------------------------------------------------------------------//

//LCD text prefix
const char firstLinePrefix[] = "Temp: ";
const char secondLinePrefix[] = "Set Temp: ";

//temperature constants
const byte maximumSetTemp = 30;
const byte minimumSetTemp = 1;
const float defaultSetTemp = 20.0f, allowableAverageTemperatureDelta = 1.0f, allowableElevationTemperatureDelta = 1.0f;

const unsigned long intervalTemperatureReading = 5000; //5 seconds, time between temperature readings, also between fan checks (but double the interval)
const unsigned long intervalCompressorOff = 900000; //900 seconds, 15 minutes. Minimum time elapsed before compressor can turn back on

//-------------------------------------------------------------------------------------------//
// #define global variables
//temperature variables
float upperTempC = 20.0f, lowerTempC = 20.0f, setTempC = defaultSetTemp, averageTempC = 20.0f;

//time variables for tracking time between activites
unsigned long previousTemperatureReadingMillis = 0; //last time temperature was read
unsigned long previousFanReadingMillis = 0; //last time fan was checked
unsigned long previousCompressorOffMillis = 0; //last time compressor turned off

//states
byte fanState = 0; //0 is off, 1 is on

//user interface state
unsigned int userInterfaceState = 0; //0 off, 1 LCD on (30 seconds timeout), 2 LCD on and temperature set (30 seconds timeout)
unsigned long currentUserInterfacemillis = 0;
unsigned long userInterfaceTimeoutInterval = 30000;

//rotary encoder variables
int encoder0Pos = 0;
int encoderButtonState; // the current reading from the input pin
int lastEncoderButtonState = LOW;   // the previous reading from the input pin
// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//fan variables
unsigned int previousFanReadMillis = 0;
int fanReadInterval = 10000;
int fanReadIntervalMultiplier = 6;
int numberOfFanReadings = 0;
int totalNumberOfFanReadingsInTheInterval = 0;
const float fanSpeedLowerLimit = 50;  //about 490 rpm
const float fanSpeedUpperLimit = 255; //about 1900 rpm
float fanSpeed = fanSpeedLowerLimit;

//-------------------------------------------------------------------------------------------//

//initializations
LiquidCrystal lcd(LCD_RS, LCD_Enable, LCD_D4, LCD_D5, LCD_D6, LCD_D7); //set up the LCD as per the notes above regarding pins

Encoder knob(Rotary_Encoder_Pin_A, Rotary_Encoder_Pin_B);

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
// arrays to hold device addresses
DeviceAddress upperThermometer, lowerThermometer;
//-------------------------------------------------------------------------------------------//

void setup() {
  Serial.begin(9600); //init serial communication

  retrieveLastSetTemperaure(); //get last set temperature

  setupDS18B20(); //setup the ds18b20 temperature sensors

  setupFan();

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(encoderButtonPin, INPUT); //Rotaty encode push button pin;
}

void loop() {
  unsigned long currentMillis = millis(); //get current time, may need this for all kinds of things this loop

  /* -----------------------------------------*/
  // check the temperature every x milli seconds (defined by intervalTemperatureReading)
  if (currentMillis - previousTemperatureReadingMillis >= intervalTemperatureReading) {
    //get the upper and lower temps
    upperTempC = sensors.getTempC(upperThermometer);
    lowerTempC = sensors.getTempC(lowerThermometer);
    Serial.print("Upper temperature: "); Serial.print(upperTempC); Serial.println(" C");
    Serial.print("Lower temperature: "); Serial.print(lowerTempC); Serial.println(" C");
    averageTempC = (upperTempC + lowerTempC)/2;
    updateLCDDisplay();//not sure if this should happen everytime. probably need to only update if changed.
    previousTemperatureReadingMillis = currentMillis; //update this.
  }
  /* -----------------------------------------*/

  currentMillis = millis(); //that may have taken some time, so get this again

  /* -----------------------------------------*/
  // check to see if fan should be running (upperTempC is too far from lowerTempC) every 2 x temperture check interval
  if (currentMillis - previousFanReadingMillis >= (2 * intervalTemperatureReading)) {
    //turn fan on if we are at the Delta
    //run at 100% until we are at 50% of delta
    //run at 50% until we are at 20% of delta
    //run at 25% until we are at 10% of delta
    //once we are at 10% of delta, turn fan off and restart

    float temperatureDelta = abs(upperTempC - lowerTempC);
    if ((fanState == 0) && (temperatureDelta > allowableElevationTemperatureDelta)) {
      turnFanOn(fanSpeedUpperLimit);  //100% on using PWM
    } else if ((fanState == 1) && (allowableElevationTemperatureDelta >= temperatureDelta > (0.5 * allowableElevationTemperatureDelta))) {
      turnFanOn((fanSpeedUpperLimit - fanSpeedLowerLimit) / 2 + fanSpeedLowerLimit); //50% on using PWM
    } else if ((fanState == 1) && ((0.5 * allowableElevationTemperatureDelta) >= temperatureDelta > (0.10 * allowableElevationTemperatureDelta))) {
      turnFanOn((fanSpeedUpperLimit - fanSpeedLowerLimit) / 4 + fanSpeedLowerLimit); //25% on using PWM
    } else if ((fanState == 1) && ((0.1 * allowableElevationTemperatureDelta) >= temperatureDelta)) {
      turnFanOff();
    }
    previousFanReadingMillis = currentMillis; //update this.
  }
  /* -------------------------------------------*/

  currentMillis = millis(); //that may have taken some time, so get this again
  if (currentMillis - previousFanReadMillis >= fanReadInterval) {
    calcFanRPM(currentMillis);
  }

  /* -------------------------------------------*/
  //Get Rotary Encode Button Press
  //Local display and temperature set work via button press
  //plan is
  //1 press = LCD display on //30 second timeout from press or rotary encoder movements
  //2 press = temperature adjust
  currentMillis = millis(); //that may have taken some time, so get this again
  int reading = digitalRead(encoderButtonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastEncoderButtonState) {
    // reset the debouncing timer
    lastDebounceTime = currentMillis;
  }

  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != encoderButtonState) {
      encoderButtonState = reading;

      // act on button press, change state 0, 1 or 2
      if (encoderButtonState == HIGH) {
        //if button presed in state 2, return to state 1
        if (userInterfaceState == 2) userInterfaceState = 1;
        else userInterfaceState++;      
        currentUserInterfacemillis = currentMillis;
      }
    }
    lastEncoderButtonState = reading;
  }
  /* -------------------------------------------*/

  /* -------------------------------------------*/
  //Handle UI state
  //0 = off
  //1 = LCD on (30 second timeout from last activity, return to state 0)
  //2 = LCD on, rotary encoder reading active for temperature set (30 second timeout).
  //    if timeout, no temperature change, lcd off -> return to state 0
  //    if button press, temp change confirmed, return to state 1

  if (userInterfaceState == 0) {    
      lcd.noDisplay();
      break;
  }else if (userInterfaceState == 1 || userInterfaceState ==2){
      lcd.display();
      if (currentMillis - currentUserInterfacemillis >= userInterfaceTimeoutInterval) {
        //timeout has occurred, no changes to be made;
        userInterfaceState = 0;
      }
  }

  /* -------------------------------------------*/
  /* -------------------------------------------*/
  // Rotary Encoder reading if we are in "userInterfaceState state 2"
  if (userInterfaceState==2) {
    long newPosition = knob.read();
    if (newPosition != encoder0Pos) {
      float positionDifference = newPosition - encoder0Pos;
      encoder0Pos = newPosition;
      currentUserInterfacemillis = currentMillis;
    }
  }
  /* -------------------------------------------*/


  /* -------------------------------------------*/
  // check to see if compressor should be running (average is too warm)
  /* -------------------------------------------*/


  /* -------------------------------------------*/
  // check to see if heater should be running (average is too cold)
  /* -------------------------------------------*/


  /* -------------------------------------------*/
  // check to see if set temperature is changed
  /* -------------------------------------------*/

}

/* -------------------------------------------*/
void updateLCDDisplay() {
  lcd.print(firstLinePrefix + String(averageTempC, 1) + "C"); //print the current averege fridge temp on the LCD
  lcd.setCursor(0, 1);
  lcd.print(secondLinePrefix + String(setTempC, 1) + "C"); //print the set temp on the LCD
}
/* -------------------------------------------*/

/* -------------------------------------------*/
//fan functions
void setupFan() {
  pinMode(fanOnPin, OUTPUT);
  digitalWrite(fanOnPin, LOW);
  fanState = 0; //set fan to OFF
  pinMode(fanSpeedPin, OUTPUT);
  analogWrite(fanSpeedPin, fanSpeed);
  pinMode(fanSpeedSensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(fanSpeedSensor), rpm, RISING);
}

void calcFanRPM(unsigned long currentMillis) {
  previousFanReadMillis = currentMillis;
  totalNumberOfFanReadingsInTheInterval = numberOfFanReadings;
  numberOfFanReadings = 0;
  int value = totalNumberOfFanReadingsInTheInterval * fanReadIntervalMultiplier;
  Serial.print("Fan RPM: ");
  Serial.println(value);
}

void rpm () {
  numberOfFanReadings++;
}

void turnFanOn(int PWMValue) {
  analogWrite(numberOfFanReadings, PWMValue);
  fanState = 1; //set fan to On
}

void turnFanOff() {
  analogWrite(numberOfFanReadings, fanSpeedLowerLimit);
  fanState = 0; //set fan to OFF
}
/* -------------------------------------------*/

/* -------------------------------------------*/
void setupDS18B20() {
  sensors.begin();    //start the DallasTemp sensors

  //set initial thermometer addresses
  if (!sensors.getAddress(upperThermometer, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(lowerThermometer, 1)) Serial.println("Unable to find address for Device 1");

  sensors.setResolution(upperThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(lowerThermometer, TEMPERATURE_PRECISION);
}
/* -------------------------------------------*/

/* -------------------------------------------*/
void retrieveLastSetTemperaure() {
  //retreive the temperature stored in the eeprom
  EEPROM.get( SetTemperatureAddress, setTempC );

  //if the temperature is outside the defined allowable range, set it to the default temperature of 20 degrees C.
  if (((float)maximumSetTemp < setTempC) || ((float)minimumSetTemp > setTempC)) setTempC = defaultSetTemp;
}
/* -------------------------------------------*/
