// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4;
const int ledPin = 7;
const int startPosPin = 2;

 
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(startPosPin, INPUT);
  digitalWrite(ledPin, HIGH);
  
}

bool direct = true;
int delayForDirection = 0;

void loop() {
    int d =2;
    digitalWrite(dirPin, direct);

    bool dirCahnged = !digitalRead(startPosPin);
    if (dirCahnged && delayForDirection==0){
      direct = !direct;
      delayForDirection = 200;
    }

    if (delayForDirection>0)
      delayForDirection--;
    
    
    if (direct){
      digitalWrite(stepPin,LOW);
      delay(d);
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(1);
    }
    else{
      digitalWrite(stepPin,HIGH);
      delay(d);
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(1);
    }

  
}