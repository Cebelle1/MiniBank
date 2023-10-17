/*CHECKPOINT*/

#include <Servo.h>
#include <Stepper.h>

//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

Servo myservo;  // create servo object to control a servo
Servo bigservo;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
const int ra0=13;
const int ra1=12;
const int ra2=7;
const int ra3=4;
const int motorpin =10;
int xTest1 =0;
int xTest2 =0;
int i;
int twentycent;
int fiftycent;
int stateRA0=0;
int stateRA1=0;
int stateRA2=0;
int stateRA3=0;
int  Steps2Take;
void setup() {
  myservo.attach(3);  // twentycent
  bigservo.attach(5); //fiftycent
  pinMode(ra0,INPUT);
  pinMode(ra1,INPUT);
  pinMode(ra2,INPUT);
  pinMode(motorpin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(motorpin,LOW);
  twentycent=0;
  fiftycent=0;
  xTest1=0;
  xTest2=0;
  stateRA2=digitalRead(ra2);
  stateRA3=digitalRead(ra3);
  while(stateRA2==0&&stateRA3==0){
    stateRA2=digitalRead(ra2);
    stateRA3=digitalRead(ra3);
  }

  //Serial.println("State of RA0" + stateRA0);
  //Serial.println("State of RA1" + stateRA1);
  Serial.println("State of RA2" );
  Serial.println(stateRA2);

  //---FOR DISPENSING COINS---//
  while(stateRA2==1){
  stateRA0=digitalRead(ra0);
  stateRA1=digitalRead(ra1);
  stateRA2=digitalRead(ra2);
    if(stateRA0==1){
      twentycent++;
    }
    Serial.println("No. of twenty cent entered:");
    Serial.println(twentycent);
    if (stateRA1==1){
      fiftycent++;
    }
    Serial.println("No. of fifty cent entered:");
    Serial.println(fiftycent);
    delay(1000);
    
  }
    for(i=0;i<twentycent;i++){         //Code for servo motor
      for (pos = 0; pos <= 140; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 140; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    }
  delay(2000);
    for(i=0;i<fiftycent;i++){         //Code for servo motor
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      bigservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(3);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      bigservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(3);                       // waits 15ms for the servo to reach the position
    }
    }
  //----FOR INSERTING COINS----//
  while(stateRA3==1){
    digitalWrite(motorpin,HIGH);
    stateRA3=digitalRead(ra3);

  }
  Serial.println("StateRA3=0");
  

}
