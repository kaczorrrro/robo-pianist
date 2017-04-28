#include "keyShifts.h"
#include "pianoMove.h"

//pins
const int buttonPin = 2;
const int stepPin = 3;
const int directionPin = 4;
const int servoPin = 5;
const int ledPin = 7;

//keyboard params - steps per key
const int dSym = 45;
const int dAsym = 53;
const int dWhiteToBlack = 26;//mayby 27?

//value for calibration
const int stepsFromLeftToFirstKey = 35;

//servo params
const int servoUpAngle = 40;
const int servoDownOnWhite = 21;
const int servoDownOnBlack = 23;

//engine param
const int engineDelay = 3;

//timeing params
const int minPressTime = 200;
const int timeForShift = 500; // max time to move from one key to another for note of length 1


//initialize services
Shifts shifts (dSym,dAsym,dWhiteToBlack);
ServoController servo(servoUpAngle, servoDownOnWhite, servoDownOnBlack);
FingerController finger(stepPin, directionPin, engineDelay, &servo, &shifts);



void setup() {
  Serial.begin(9600);
  
  servo.attach(servoPin);
  servo.up();
  
  pinMode(stepPin,OUTPUT);
  pinMode(directionPin,OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}




void loop() {
  if (digitalRead(buttonPin)) //wait for button to be pushed
    return;
    
  finger.calibrate(buttonPin, stepsFromLeftToFirstKey);  

  //these two arrays should be placed somewhere else..., but be careful, since this version depends on sizeof(array), that doesn't work for pointers!
  char notes [] = {
    KEY_A3, KEY_C4, KEY_D4, KEY_D4, 
    KEY_D4, KEY_E4, KEY_F4, KEY_F4,
    KEY_F4, KEY_G4, KEY_E4, KEY_E4,
    //8
    KEY_D4, KEY_C4, KEY_C4, KEY_D4,
    KEY_A3, KEY_C4, KEY_D4, KEY_D4,
    KEY_D4, KEY_E4, KEY_F4, KEY_F4,
    KEY_E4, KEY_E4, KEY_D4, KEY_C4,
    KEY_D4, KEY_A3, KEY_C4,
    KEY_D4, KEY_D4, KEY_D4, KEY_F4,
    KEY_G4, KEY_G4, KEY_G4, KEY_A4,
    KEY_AIS4, KEY_AIS4, KEY_A4, KEY_G4,
    //16
    KEY_A4, KEY_D4
  };

  char len [] = {
    1,1,2,2,
    1,1,2,2,
    1,1,2,2,
    //8
    1,1,1,3,
    1,1,2,2,
    1,1,2,2,
    2,2,1,1,
    4,1,1,
    2,2,1,1,
    2,2,1,1,
    2,2,1,1,
    //16
    1,3,1,1
  };
  
  unsigned long t0;
  t0 = millis()+1000; //play the first note when one second passes

  //buffer for messages, probably not in the best place
  char message [100];

  for (int i=0, n=sizeof(notes);i<n;i++){
    finger.moveToKey(notes[i]);

    //caluclate how much time we have before we should play current note
    int timeLeft = (int)(t0-millis());
    sprintf(message, "Time left: %d\n", timeLeft);
    Serial.print(message);

    if (timeLeft>0)
      delay(timeLeft);

    //calculate the time when next note should be played
    t0 = millis() + timeForShift*len[i];

    int pressingTime = minPressTime;
    //if current key is not the shortest lasting one, we can hold finger a little longer
    if (len[i]>1)
      pressingTime+=timeForShift*0.8*(len[i]-1);
    
    finger.press(pressingTime);
  }
  
}
