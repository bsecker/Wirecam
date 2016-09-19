#include <Servo.h>


/*--------------PIN DEFINITIONS---------------*/
const int yaw_servo_pin = 11;
const int motor_pin = 10;

const int ch1_pin = 5; // wheel
const int ch2_pin = 6; // motor
const int ch3_pin = 9; // button
const int buzzer_pin = 12;

int DEBUG = 1;
int old_value = 0;
int new_value = 0;
Servo yaw_servo;

void setup() {
  // initialise pins
  pinMode(ch1_pin, INPUT);
  pinMode(ch2_pin, INPUT);
  pinMode(ch3_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  
  yaw_servo.attach(yaw_servo_pin);
  if (DEBUG == 1){
    Serial.begin(9600);
  }
  
}

void loop() {
  int ch1, ch2, ch3;

  ch1 = pulseIn(ch1_pin, HIGH, 25000); // wheel
  ch2 = pulseIn(ch2_pin, HIGH, 25000); // motor
  ch3 = pulseIn(ch3_pin, HIGH, 25000); // button

  //print incoming messages
  if (DEBUG == 1){
    Serial.print(ch1);
    Serial.print("   ");
    Serial.print(ch2);
    Serial.print("   ");
    Serial.print(ch3);
    Serial.println("   ");
  }
  
  if (is_pushed(ch3)){
    move_tilt(ch1);
    yaw_servo.write(90); // stop servo
  }  
  else {
    move_servo(ch1);    
  }

  new_value = is_pushed(ch3);
  if (new_value != old_value){
      old_value = new_value;
      buzzer_beep();
  } 
  
  delay(100);
}

int is_pushed(int ch) {
  // Returns true if the pushbutton is pushed
  if (ch > 1500){ // 1500 is rougly halfway between the two recieved pulse values for 1 and 0
    return 1; 
  }
  else {
    return 0;
  }
}

void move_tilt(int ch) {
 //  interface with the gimbal, currently not implemented
 ;
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

void buzzer_beep(){
  // beep buzzer twice
  for (int i = 0; i <= 1; i++) {
    digitalWrite(buzzer_pin, HIGH);
    delay(100);
    digitalWrite(buzzer_pin, LOW);
    delay(100);
  }
}
