#include <OneWire.h>            //to enable the DS18B20s
#include <DallasTemperature.h>  //to manipulate the DS18B20s
#include <LiquidCrystal.h>      //to set up the LCD

// #define constants
//temperature sensor pins
#define ONE_WIRE_BUS 10
//other definitions
#define TEMPERATURE_PRECISION 11    //11=.0125C, 375ms used to select less precise temperature
//LCD pins
#define LCD_RS 12
#define LCD_Enable 11
#define LCD_D4 7
#define LCD_D5 6
#define LCD_D6 5
#define LCD_D7 4

#define LCDBacklightOnPin 13 //via TIP120 darlington

unsigned long previousTemperatureReadingMillis = 0; //last time temperature was read
const unsigned long intervalTemperatureReading = 5000; //5 seconds, time between temperature readings, also between fan checks (but double the interval)

//temperature variables
float upperTempC = 20.0f, lowerTempC = 20.0f, averageTempC = 20.0f;

//initializations
LiquidCrystal lcd(LCD_RS, LCD_Enable, LCD_D4, LCD_D5, LCD_D6, LCD_D7); //set up the LCD as per the notes above regarding pins
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
// arrays to hold device addresses
DeviceAddress upperThermometer, lowerThermometer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //init serial communication
  pinMode(LCDBacklightOnPin, OUTPUT);
  digitalWrite(LCDBacklightOnPin, HIGH);
  setupDS18B20(); //setup the ds18b20 temperature sensors

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis(); //get current time, may need this for all kinds of things this loop

  /* -----------------------------------------*/
  // check the temperature every x milli seconds (defined by intervalTemperatureReading)
  if (currentMillis - previousTemperatureReadingMillis >= intervalTemperatureReading) {
    //get the upper and lower temps
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures();
    Serial.println("DONE");
    upperTempC = sensors.getTempC(upperThermometer);
    lowerTempC = sensors.getTempC(lowerThermometer);
    Serial.print("Upper temperature: "); Serial.print(upperTempC); Serial.println(" C");
    Serial.print("Lower temperature: "); Serial.print(lowerTempC); Serial.println(" C");
    averageTempC = (upperTempC + lowerTempC) / 2;
    Serial.print("Average temperature: "); Serial.print(averageTempC); Serial.println(" C");
    updateLCDDisplay();//not sure if this should happen everytime. probably need to only update if changed.
    previousTemperatureReadingMillis = currentMillis; //update this.
  }
  /* -----------------------------------------*/
}

/* -------------------------------------------*/
void updateLCDDisplay() {  
  lcd.setCursor(0, 0);
  lcd.print("U " + String(upperTempC, 1) + "C:D " + String(lowerTempC, 1) + "C"); //print the current averege fridge temp on the LCD
  lcd.setCursor(0, 1);
  lcd.print("AVG " + String(averageTempC, 1) + "C"); //print the set temp on the LCD
}
/* -------------------------------------------*/

/* -------------------------------------------*/
void setupDS18B20() {
  sensors.begin();    //start the DallasTemp sensors

  //set initial thermometer addresses
  if (!sensors.getAddress(upperThermometer, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(lowerThermometer, 1)) Serial.println("Unable to find address for Device 1");

  Serial.print("upperThermometer Address: ");
  printAddress(upperThermometer); Serial.println("");
  Serial.print("lowerThermometer Address: ");
  printAddress(lowerThermometer); Serial.println("");

  sensors.setResolution(upperThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(lowerThermometer, TEMPERATURE_PRECISION);
}
/* -------------------------------------------*/


// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

