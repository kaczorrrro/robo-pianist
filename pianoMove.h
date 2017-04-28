/*
	Simple interface for moving the finger
	Written by Sebastian Kaczor
*/
#pragma once

#include "keyShifts.h"
#include <Servo.h> 

class ServoController{
public:
	ServoController(int servoPin, int servoUpAngle, int servoDownForWhiteAngle, int servoDownForBlackAngle){
		this->servoUpAngle = servoUpAngle;
		this->servoDownForWhiteAngle = servoDownForWhiteAngle;
		this->servoDownForBlackAngle = servoDownForBlackAngle;
		fingerServo.attach(servoPin);
	}
	
	void whiteDown(){
		myservo.write(servoDownForWhiteAngle);
	}
	
	void blackDown(){
		myservo.write(servoDownForBlackAngle);
	}
	
	void up(){
		myservo.write(servoUpAngle);
	}
	
	
	
private:
	Servo fingerServo;
	int servoUpAngle, servoDownForWhiteAngle, servoDownForBlackAngle;
}


class FingerController{
public:
	FingerController(int stepPin, int dirPin, int engineDelay, ServoController  * fingerServo){
		this->dirPin = dirPin;
		this->stepPin = stepPin;
		this->engineDelay = engineDelay;
		this->fingerServo = fingerServo;
	}
	
	void calibrate(){
		//Code for calibration from button
		currentPos = 0;
	}
	
	void moveToKey(int key){
		int nextKeyPos = shifts[key];
		int diff = abs(nextKeyPos-currentPos);
		
		if (diff == 0)
			return;
		
		if (nextKeyPos > currentPos)
			moveRight(diff);
		else 
			moveLeft(diff);
		
		currentPos = nextKeyPos;
	}
	
	void press(int pressTime){
		//TODO
		fingerServo.whiteDown();
		delay(pressTime);
		fingerServo.up();
	}
	
	
private:
	int engineDelay;
	int currentPos;
	int stepPin;
	int dirPin;
	ServoController * fingerServo;
	
	//directionPin = HIGH -> go closer to engine
	//directionPin == stepPin -> no move
	
	void moveLeft(int steps){
		digitalWrite(dirPin, HIGH);
		for (int i=0;i<steps;i++){
			digitalWrite(stepPin,HIGH);
			delay(engineDelay);
			digitalWrite(stepPin,LOW); 
			delayMicroseconds(1);
		}
		digitalWrite(stepPin,HIGH);
	}
	
	void moveRight(int steps){
		digitalWrite(dirPin, LOW);
		for (int i=0;i<steps;i++){
			digitalWrite(stepPin,LOW);
			delay(engineDelay);
			digitalWrite(stepPin,HIGH); 
			delayMicroseconds(1);
		}
		digitalWrite(stepPin,LOW);
	}

}







//white to black 26
//dsym 45
//dasym 53