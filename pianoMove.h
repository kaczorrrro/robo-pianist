/*
	Simple interface for moving the finger
	Written by Sebastian Kaczor
*/
#include "keyShifts.h"

class FingerController{
public:

	FingerController(int stepPin, int dirPin,int engineDelay){
		this->dirPin = dirPin;
		this->stepPin = stepPin;
		this->engineDelay = engineDelay;
	}
	
	void calibrate(){
		//Code for calibration from button
		currentPos = 0;
	}
	
	void moveToKey(int key){
		int nextKeyPos = shifts[key];
		int diff = abs(nextKeyPos-curr_symbol);
		
		if (diff == 0)
			return;
		
		if (nextKeyPos > currentPos)
			moveRight(diff);
		else 
			moveLeft(diff);
		
		currentPos = nextKeyPos;
	}
	
	
private:
	int engineDelay;
	int currentPos;
	int stepPin;
	int dirPin;
	
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