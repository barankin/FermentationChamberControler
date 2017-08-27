//PWM, on, off all working
//RPM sense not correct yet!

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
#define fanSpeedSensor 2 //interupt pin for tracking fan RPM

//-------------------------------------------------------------------------------------------//
// #define global variables
//states
byte fanState = 0; //0 is off, 1 is on

//fan variables
unsigned long previousFanReadMillis = 0;
unsigned long fanReadInterval = 5000;
int fanReadIntervalMultiplier = 3;
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
    Serial.println("");
    serialInput.toLowerCase();
    serialInput.trim();
    if(serialInput.equals("off")){
        turnFanOff();
        Serial.println("Fan is off");
    }else if(serialInput.equals("full")){
        turnFanOn(fanSpeedUpperLimit);
        Serial.println("Fan is on full");
    }else if(serialInput.equals("half")){
        turnFanOn((fanSpeedUpperLimit-fanSpeedLowerLimit)/2);
        Serial.println("Fan is on half");
    }else if(serialInput.equals("low")){
        turnFanOn(fanSpeedLowerLimit);
        Serial.println("Fan is on low");
    }else{
      Serial.println("Not a recognized command");
    }
    Serial.println(serialInput);
    Serial.println("");
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
  //Serial.print("currentMillis: ");
  //Serial.println(currentMillis);
  //Serial.print("previousFanReadMillis: ");
  //Serial.println(previousFanReadMillis);
  previousFanReadMillis = currentMillis;
  
  Serial.println(numberOfFanReadings);
  totalNumberOfFanReadingsInTheInterval = numberOfFanReadings;

  Serial.print("No of Fan Reading: ");
  Serial.println(totalNumberOfFanReadingsInTheInterval);
  
  int value = totalNumberOfFanReadingsInTheInterval * fanReadIntervalMultiplier;
  
  Serial.print("Fan RPM: ");
  Serial.println(value);
  numberOfFanReadings = 0;
}

void rpm () {
  //Serial.println(numberOfFanReadings);
  numberOfFanReadings++;
}

void turnFanOn(int PWMValue) {
  Serial.print("Fan running at PWM of: ");
  Serial.println(PWMValue);
  analogWrite(fanSpeedPin, PWMValue);
  fanState = 1; //set fan to On
  digitalWrite(fanOnPin, HIGH);
}

void turnFanOff() {
  analogWrite(fanSpeedPin, 0);
  fanState = 0; //set fan to OFF
  digitalWrite(fanOnPin, LOW);
}
/* -------------------------------------------*/
