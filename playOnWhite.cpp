#include <Servo.h> 

class Test{
  int i = 1;

public:
  void chage(){
    i++;
  }
};

const int stepPin = 3; 
const int dirPin = 4;
const int servoPin = 5;
const int ledPin = 7;
const int startPosPin = 2;

const double stepsPerKey = 45;

Servo myservo;
 
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(startPosPin, INPUT);
  digitalWrite(ledPin, HIGH);

  myservo.attach(servoPin);
  myservo.write(40);
}

bool runnin = false;


void press(){
  myservo.write(17);
  delay(100);
  myservo.write(40);
}

void move(int steps){
  int d = 5;
  for (int i=0;i<steps;i++){
    digitalWrite(stepPin,LOW);
    delay(d);
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1);
  }
}


void loop() {
    if (!digitalRead(startPosPin))
      runnin = true;
      
    
    if (runnin){
      double pos = 0.0;
      int posRounded = 0;
      int lastPos = 0;
      for (int i=0;i<10;i++){
        for (int j=0;j<4;j++){
          press();
          delay(100);
        }

        pos+=stepsPerKey;
        posRounded = round(pos);
        
        move(posRounded-lastPos);
        lastPos = posRounded;

      }
      runnin=false;
    }
  
}