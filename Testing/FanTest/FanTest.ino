

/* function declaration */
void setupFan();
void turnFanOn(int PWMValue);
void turnFanOff();
void calcFanRPM(unsigned long currentMillis);
void rpm ();

//-------------------------------------------------------------------------------------------//
// #define constants
//temperature sensor pins
#define ONE_WIRE_BUS 10
#define fanOnPin A0

//fan pin
#define fanSpeedPin 9 //pwm pin
#define fanSpeedSensor 3 //interupt pin for tracking fan RPM

//-------------------------------------------------------------------------------------------//
// #define global variables
//states
byte fanState = 0; //0 is off, 1 is on

//fan variables
unsigned int previousFanReadMillis = 0;
int fanReadInterval = 10000;
int fanReadIntervalMultiplier = 6;
int numberOfFanReadings = 0;
int totalNumberOfFanReadingsInTheInterval = 0;
const float fanSpeedLowerLimit = 50;  //about 490 rpm
const float fanSpeedUpperLimit = 255; //about 1900 rpm
float fanSpeed = fanSpeedLowerLimit;

unsigned int fanSpeedState = 0; //0 is off, 1 is full, 2 is half, 3 is low


unsigned int previousFanActionMillis = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //init serial communication
  setupFan();

}

void loop() {
  unsigned long currentMillis = millis(); //get current time, may need this for all kinds of things this loop

  //get fan speed
  if (currentMillis - previousFanReadMillis >= fanReadInterval) {
    calcFanRPM(currentMillis);
  }

    
  if (currentMillis - previousFanActionMillis >= (fanReadInterval*2)) {
    if(fanSpeedState == 0){
      turnFanOff();
      fanSpeedState++;      
    }else if (fanSpeedState == 1){
      turnFanOn(255);
      fanSpeedState++;
    }else if (fanSpeedState == 2){
      turnFanOn(255/2);
      fanSpeedState++;
    }else if (fanSpeedState == 3){
      turnFanOn(0);
      fanSpeedState++;
    }
  }

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
