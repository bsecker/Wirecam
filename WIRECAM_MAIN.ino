#include <Servo.h>


/*--------------PIN DEFINITIONS---------------*/
const int yaw_servo_pin = 11;
const int motor_pin = 10;

const int ch1_pin = 5; // servo
const int ch2_pin = 6; // motor
const int ch3_pin = 3; // button



Servo yaw_servo;

void setup() {
  // 
  pinMode(ch1_pin, INPUT);
  pinMode(ch2_pin, INPUT);
  pinMode(ch3_pin, INPUT);
  
  pinMode(motor_pin, OUTPUT);
  yaw_servo.attach(yaw_servo_pin);
  Serial.begin(9600);
  
}

void loop() {
  int ch1, ch2, ch3, pos;

  ch1 = pulseIn(ch1_pin, HIGH, 25000); // servo
  ch2 = pulseIn(ch2_pin, HIGH, 25000); // motor
  ch3 = pulseIn(ch3_pin, HIGH, 25000); // button

  //print incoming messages
  Serial.print(ch1);
  Serial.print("   ");
  Serial.print(ch2);
  Serial.print("   ");
  Serial.print(ch3);
  Serial.println("   ");
  
  move_servo(ch1);
  delay(100);
}

void move_motor(int ch){
  //where ch = channel 2 raw input
  //no longer used
  ch = map(ch, 1000, 1750, 0, 255);
  analogWrite(motor_pin, ch); 
}


// TO DO: implement constraints for servo
void move_servo(int ch){
  //where ch = channel 1 raw input
  int pos;

  // if reciever is on, write:
  if (ch != 0) {
    pos = map(ch, 1000, 2000, 0, 180);
    // Dead zone
    if (pos <= 80 || pos >= 95) {
      yaw_servo.write(pos);
    }
    else{
      yaw_servo.write(90);
    }
  }
}
