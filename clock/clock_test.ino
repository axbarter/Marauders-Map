int led1 = 5;
int led2 = 6;
int led3 = 7;
int led4 = 8;

int val = 0;
int val1 = 0;
int val2 = 0;
int count =0;

#include <Servo.h>

Servo point;
Servo sweep;  

int pos = 0;
int speed = 90;

void setup() {
  // put your setup code here, to run once:
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
point.attach(11);
sweep.attach(12);
digitalWrite(led1,1);
delay(1000);
digitalWrite(led2,1);
delay(1000);
digitalWrite(led3,1);
delay(1000);
digitalWrite(led4,1);
delay(1000);
digitalWrite(led1,0);
digitalWrite(led2,0);
digitalWrite(led3,0);
digitalWrite(led4,0);
 Serial.begin(9600);
Serial.print("Setup all done  ");
Serial.print("\r");
}
void loop() {

//  // put your main code here, to run repeatedly:

    //reset LEDs
  digitalWrite(led1,0);
  digitalWrite(led2,0);
  digitalWrite(led3,0);
  digitalWrite(led4,0);
//check to see if person 1 is home  
  digitalWrite(led3,1);
  pinMode(2, INPUT_PULLUP);
 
  val = digitalRead(2);
  
  Serial.print("Digital Input 2 ");
  Serial.print('\r');
  Serial.print(val);
  Serial.print('\r');
  if (val == 1)
    {
      point.write(10);
          // check LEDs before moving on
      digitalWrite(led4,1);
      digitalWrite(led2,0);
    }
    else
    {
      point.write(170);
      digitalWrite(led2,1);
      digitalWrite(led4,0);
    }
// move hands round before checking for next person
for (count = 0; count <=30; count +=1){
    sweep.attach(12);
  sweep.write(87);
  delay(110);
  sweep.detach();
  delay(890);
  }
  //reset LEDs
  digitalWrite(led1,0);
  digitalWrite(led2,0);
  digitalWrite(led3,0);
  digitalWrite(led4,0);
  digitalWrite(led1,1);

// Check to see if person 2 is home
  pinMode(3, INPUT_PULLUP);
 
  val2 = digitalRead(3);
  
    Serial.print("Digital Input 3");
    Serial.print('\r');
  Serial.print(val2);
  Serial.print('\r');
  if (val2 == 1)
    {
      point.write(10);
          // check LEDs before moving on
      digitalWrite(led4,1);
      digitalWrite(led2,0);
    }
    else
    {
      point.write(170);
      digitalWrite(led2,1);
      digitalWrite(led4,0);
    }

    for (count = 0; count <=30; count +=1){
    sweep.attach(12);
  sweep.write(87);
  delay(110);
  sweep.detach();
  delay(890);
  }
}
