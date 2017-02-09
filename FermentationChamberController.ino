
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
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
*/
#include <OneWire.h>            //to enable the DS18B20s
#include <DallasTemperature.h>  //to manipulate the DS18B20s
#include <LiquidCrystal.h>      //to set up the LCD
#include <EEPROM.h>             //to retrieve/save last set temperature


/* function declaration */
void setupDS18B20();
void retrieveLastSetTemperaure();
void turnFanOn(int PWMValue);
void turnFanOff();

// #define constants
//temperature sensor pins
#define ONE_WIRE_BUS 10
#define TEMPERATURE_PRECISION 11

//fan pin
#define Fan 9 //pwm pin

//relay pins
#define Heater_Relay 7
#define Compressor_Relay 6

//rotary encoder pins
#define Rotary_Pin_A A0
#define Rotary_Pin_B A1

//LCD pins
#define LCD_RS 12
#define LCD_Enable 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

//eeprom address
#define SetTemperatureAddress 0

//LCD text prefix
const char firstLinePrefix[] = "Temp: ";
const char secondLinePrefix[] = "Set Temp: ";

//temperature constants
const byte maximumSetTemp = 30;
const byte minimumSetTemp = 1;
const float defaultSetTemp = 20.0f, allowableAverageTemperatureDelta = 1.0f, allowableElevationTemperatureDelta = 1.0f;

const unsigned long intervalTemperatureReading = 5000; //5 seconds, time between temperature readings, also between fan checks
const unsigned long intervalCompressorOff = 900000; //900 seconds, 15 minutes. Minimum time elapsed before compressor can turn back on

// #define global variables
//temperature variables
float upperTempC = 20.0f, lowerTempC = 20.0f, setTempC = defaultSetTemp, averageTempC = 20.0f;

//time variables for tracking time between activites
unsigned long previousTemperatureReadingMillis = 0; //last time temperature was read
unsigned long previousFanReadingMillis = 0; //last time fan was checked
unsigned long previousCompressorOffMillis = 0; //last time compressor turned off

//states
byte fanState = 0; //0 is off, 1 is on

//initializations
LiquidCrystal lcd(LCD_RS, LCD_Enable, LCD_D4, LCD_D5, LCD_D6, LCD_D7); //set up the LCD as per the notes above regarding pins

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
// arrays to hold device addresses
DeviceAddress upperThermometer, lowerThermometer;

void setup() {
  Serial.begin(9600); //init serial communication
  
  retrieveLastSetTemperaure(); //get last set temperature
  
  setupDS18B20(); //setup the ds18b20 temperature sensors

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  //setup I/O pins
  pinMode(Fan, OUTPUT);
  
}

void loop() {
  unsigned long currentMillis = millis(); //get current time, may need this for all kinds of things this loop

  /* -----------------------------------------*/
  // check the temperature every x milli seconds (defined by intervalTemperatureReading)
  if (currentMillis - previousTemperatureReadingMillis >= intervalTemperatureReading) {
    //get the upper and lower temps
    upperTempC = sensors.getTempC(upperThermometer);
    lowerTempC = sensors.getTempC(lowerThermometer);
    averageTempC = (upperTempC + lowerTempC);
    updateLCDDisplay();//not sure if this should happen everytime. probably need to only update if changed.
    previousTemperatureReadingMillis = currentMillis; //update this.
  }
  /* -----------------------------------------*/


  /* -----------------------------------------*/
  // check to see if fan should be running (upperTempC is too far from lowerTempC)
  
  if (currentMillis - previousFanReadingMillis >= intervalTemperatureReading) {
    //turn fan on if we are at the Delta
    //run at 100% until we are at 50% of delta
    //run at 50% until we are at 20% of delta
    //run at 25% until we are at 10% of delta
    //once we are at 10% of delta, turn fan off and restart

    float temperatureDelta = abs(upperTempC - lowerTempC);
    if ((fanState == 0) && (temperatureDelta > allowableElevationTemperatureDelta))
      turnFanOn(255);  //100% on using PWM
    }else if((fanState == 1) && (allowableElevationTemperatureDelta >= temperatureDelta > (0.5 * allowableElevationTemperatureDelta))){
      turnFanOn(127); //50% on using PWM
    }else if((fanState == 1) && ((0.5*allowableElevationTemperatureDelta) >= temperatureDelta > (0.10 * allowableElevationTemperatureDelta))){
      turnFanOn(56); //25% on using PWM
    }else if((fanState == 1) && ((0.1*allowableElevationTemperatureDelta) >= temperatureDelta)){
      turnFanOff();
    }
    previousFanReadingMillis = currentMillis; //update this.
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
void updateLCDDisplay(){
  lcd.print(firstLinePrefix + String(averageTempC,1) + "C"); //print the current averege fridge temp on the LCD
  lcd.setCursor(0,1);
  lcd.print(secondLinePrefix + String(setTempC,1) + "C"); //print the set temp on the LCD
}
/* -------------------------------------------*/

/* -------------------------------------------*/
//fan functions
void turnFanOn(int PWMValue){
    analogWrite(Fan,PWMValue);
    fanState = 1; //set fan to On
}

void turnFanOff(){
    analogWrite(Fan,0);
    fanState = 0; //set fan to On
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
