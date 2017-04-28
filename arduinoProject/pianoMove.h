/*
	Simple interface for moving the finger
	Written by Sebastian Kaczor
*/
#pragma once

#include "keyShifts.h"
#include <Servo.h> 
class ServoController {
public:
	ServoController(int servoPin, int servoUpAngle, int servoDownForWhiteAngle, int servoDownForBlackAngle) {
		this->servoUpAngle = servoUpAngle;
		this->servoDownForWhiteAngle = servoDownForWhiteAngle;
		this->servoDownForBlackAngle = servoDownForBlackAngle;
		fingerServo.attach(servoPin);
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

	void calibrate() {
		//Code for calibration from button
		currentPos = 0;
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
	}

	void press(int pressTime) {
		//TODO
		fingerServo->whiteDown();
		delay(pressTime);
		fingerServo->up();
	}


private:
	int engineDelay;
	int currentPos;
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