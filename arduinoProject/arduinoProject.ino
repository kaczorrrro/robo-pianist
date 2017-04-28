#include "keyShifts.h"
#include "pianoMove.h"

const int buttonPin = 2;
const int stepPin = 3;
const int directionPin = 4;
const int servoPin = 5;
const int ledPin = 7;

const int dSym = 45;
const int dAsym = 53;
const int dWhiteToBlack = 26;//mayby 27?
const int stepsFromLeftToFirstKey = 35;

const int servoUpAngle = 40;
const int servoDownOnWhite = 21;
const int servoDownOnBlack = 23;

const int engineDelay = 3;

const int minPressTime = 200;
const int timeForShift = 500;


Shifts shifts (dSym,dAsym,dWhiteToBlack);
ServoController servo(servoUpAngle, servoDownOnWhite, servoDownOnBlack);
FingerController finger(stepPin, directionPin, engineDelay, &servo, &shifts);



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  servo.attach(servoPin);
  servo.up();
  pinMode(stepPin,OUTPUT);
  pinMode(directionPin,OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  

}




void loop() {
  if (digitalRead(buttonPin))
    return;
    
  finger.calibrate(buttonPin, stepsFromLeftToFirstKey);  

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
  
  unsigned long t0, tStart;
  tStart = millis();
  t0 = millis()+1000;//reasonable random value

  char message [100];

  for (int i=0, n=sizeof(notes);i<n;i++){
    finger.moveToKey(notes[i]);

    int timeLeft = (int)(t0-millis());
    sprintf(message, "Time left: %d\n", timeLeft);
    Serial.print(message);

    if (timeLeft>0)
      delay(timeLeft);

    t0 = millis() + timeForShift*len[i];

    int pressingTime = minPressTime;
    //if current key is not the shortest lasting one, we can hold finger a little longer
    if (len[i]>1)
      pressingTime+=timeForShift*0.8*(len[i]-1);
    
    finger.press(pressingTime);
  }
  
  
//  finger.moveToKey(KEY_C5);
  // put your main code here, to run repeatedly:
  //
  //
  
}
