

/* function declaration */
void setupFan();
void turnFanOn(int PWMValue);
void turnFanOff();
void calcFanRPM(unsigned long currentMillis);
void rpm ();

//-------------------------------------------------------------------------------------------//
// #define constants
//temperature sensor pins
#define fanOnPin A0

//fan pin
#define fanSpeedPin 9 //pwm pin
#define fanSpeedSensor 3 //interupt pin for tracking fan RPM

//-------------------------------------------------------------------------------------------//
// #define global variables
//states
byte fanState = 0; //0 is off, 1 is on

//fan variables
unsigned long previousFanReadMillis = 0;
int fanReadInterval = 10000;
int fanReadIntervalMultiplier = 6;
int numberOfFanReadings = 0;
int totalNumberOfFanReadingsInTheInterval = 0;
const float fanSpeedLowerLimit = 50;  //about 490 rpm
const float fanSpeedUpperLimit = 255; //about 1900 rpm
float fanSpeed = fanSpeedLowerLimit;
unsigned int fanSpeedState = 1; //0 is off, 1 is full, 2 is half, 3 is low
unsigned long previousFanActionMillis = 0;

String serialInput;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //init serial communication
  Serial.println("Starting fan test");
  setupFan();

}

void loop() {
  unsigned long currentMillis = millis(); //get current time, may need this for all kinds of things this loop

  //get fan speed
  if (currentMillis - previousFanReadMillis >= fanReadInterval) {
    calcFanRPM(currentMillis);
  }

  while (Serial.available()) {
    serialInput = Serial.readString(); // read the incoming data as string
    Serial.println(serialInput);
    if(serialInput.toLowerCase().equals("off")){
        turnFanOff();
        Serial.println("Fan is off");
    }else if(serialInput.toLowerCase().equals("full")){
        turnFanOn(255);
        Serial.println("Fan is on full");
    }else if(serialInput.toLowerCase().equals("half")){
        turnFanOn(255/2);
        Serial.println("Fan is on half");
    }else if(serialInput.toLowerCase().equals("low")){
        turnFanOn(0);
        Serial.println("Fan is on low");
    }
  }

  /**
    if (currentMillis - previousFanActionMillis >= (fanReadInterval * 2)) {
      if (fanSpeedState == 0) {
        turnFanOff();
        Serial.println("Fan is off");
        fanSpeedState++;
      } else if (fanSpeedState == 1) {
        turnFanOn(255);
        Serial.println("Fan is on full");
        fanSpeedState++;
      } else if (fanSpeedState == 2) {
        Serial.println("Fan is on half");
        turnFanOn(255 / 2);
        fanSpeedState++;
      } else if (fanSpeedState == 3) {
        Serial.println("Fan is on low");
        turnFanOn(0);
        fanSpeedState++;
      }
      previousFanActionMillis = currentMillis;
    }
    **/

}


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
  Serial.print("currentMillis: ");
  Serial.println(currentMillis);
  Serial.print("previousFanReadMillis: ");
  Serial.println(previousFanReadMillis);
  previousFanReadMillis = currentMillis;
  totalNumberOfFanReadingsInTheInterval = numberOfFanReadings;

  Serial.print("No of Fan Reading: ");
  Serial.println(totalNumberOfFanReadingsInTheInterval);
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
  digitalWrite(fanOnPin, HIGH);
}

void turnFanOff() {
  analogWrite(numberOfFanReadings, fanSpeedLowerLimit);
  fanState = 0; //set fan to OFF
  digitalWrite(fanOnPin, LOW);
}
/* -------------------------------------------*/
