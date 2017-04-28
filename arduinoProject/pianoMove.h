/*
	Simple interface for moving the finger
	Written by Sebastian Kaczor
*/
#pragma once

#include "keyShifts.h"
#include <Servo.h> 
class ServoController {
public:
	ServoController(int servoUpAngle, int servoDownForWhiteAngle, int servoDownForBlackAngle) {
		this->servoUpAngle = servoUpAngle;
		this->servoDownForWhiteAngle = servoDownForWhiteAngle;
		this->servoDownForBlackAngle = servoDownForBlackAngle;
	}

	void whiteDown() {
		fingerServo.write(servoDownForWhiteAngle);
	}

	void blackDown() {
		fingerServo.write(servoDownForBlackAngle);
	}

	void up() {
		fingerServo.write(servoUpAngle);
	}
	
	void attach(int servoPin){
		fingerServo.attach(servoPin);
	}



private:
	Servo fingerServo;
	int servoUpAngle, servoDownForWhiteAngle, servoDownForBlackAngle;
};


class FingerController {
public:
	FingerController(int stepPin, int dirPin, int engineDelay, ServoController  * fingerServo, Shifts * shifts) {
		this->dirPin = dirPin;
		this->stepPin = stepPin;
		this->engineDelay = engineDelay;
		this->fingerServo = fingerServo;
		this->shifts = shifts;
	}

	//Code for calibration from button
	//Button not pressed -> true
	void calibrate(int buttonPin, int stepsFromLeftSide) {
		delay(200); //Since clicking button starts calibration, we should wait some time to make sure button is no longer pressed
		
		//after calibration we point to first key
		currentPos = 0;
		currentKey = KEY_F3;
		
		while (digitalRead(buttonPin)) 
			moveLeft(2);
		
		//after stopping we are on max left side, so now lets move a little right to point to first key
		delay(10);
		moveRight(stepsFromLeftSide);
		delay(2000);
	}

	void moveToKey(char key) {
		int nextKeyPos = shifts->getShift(key);
		int diff = abs(nextKeyPos - currentPos);
		if (diff == 0)
			return;

		if (nextKeyPos > currentPos)
			moveRight(diff);
		else
			moveLeft(diff);

		currentPos = nextKeyPos;
		currentKey = key;
	}

	void press(int pressTime) {
		if (Shifts::isBlack(currentKey))
			fingerServo->blackDown();
		else
			fingerServo->whiteDown();
		
		delay(pressTime);
		fingerServo->up();
	}


private:
	int engineDelay;
	int currentPos;
	char currentKey;
	int stepPin;
	int dirPin;
	ServoController * fingerServo;
	Shifts * shifts;

	//directionPin = HIGH -> go closer to engine
	//directionPin == stepPin -> no move

	void moveLeft(int steps) {
		digitalWrite(dirPin, HIGH);
		for (int i = 0; i<steps; i++) {
			digitalWrite(stepPin, HIGH);
			delay(engineDelay);
			digitalWrite(stepPin, LOW);
			delayMicroseconds(1);
		}
		digitalWrite(stepPin, HIGH);
	}

	void moveRight(int steps) {
		digitalWrite(dirPin, LOW);
		for (int i = 0; i<steps; i++) {
			digitalWrite(stepPin, LOW);
			delay(engineDelay);
			digitalWrite(stepPin, HIGH);
			delayMicroseconds(1);
		}
		digitalWrite(stepPin, LOW);
	}

};







//white to black 26
//dsym 45
//dasym 53