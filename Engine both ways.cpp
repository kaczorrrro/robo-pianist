// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4;
const int ledPin = 7;
 
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, HIGH);
}

//rotation direction
bool direct = true;

void loop() {
  direct = !direct;
  digitalWrite(dirPin, direct);
  
  int d = 3;
  
  for(int x = 0; x < 400; x++) {
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

  digitalWrite(stepPin,HIGH);
  digitalWrite(ledPin, HIGH);
  digitalWrite(dirPin, LOW);
  delay(1000);
  digitalWrite(ledPin, LOW);
}