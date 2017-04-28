#include "keyShifts.h"
#include "pianoMove.h"

const int stepPin = 3;
const int directionPin = 4;
const int servoPin = 5;
const int ledPin = 7;

const int dSym = 45;
const int dAsym = 53;
const int dWhiteToBlack = 26;

const int servoUpAngle = 40;
const int servoDownOnWhite = 7;
const int servoDownOnBlack = 17;

const int engineDelay = 4;


Shifts shifts (dSym,dAsym,dWhiteToBlack);
ServoController servo(servoPin, servoUpAngle, servoDownOnWhite, servoDownOnBlack);
FingerController finger(stepPin, directionPin, engineDelay, &servo, &shifts);


void setup() {
  // put your setup code here, to run once:
  

}

void loop() {
  // put your main code here, to run repeatedly:
  //finger.moveToKey(KEY_C5);
  finger.press(1000);

}
