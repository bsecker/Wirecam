#include <Servo.h>


// PIN DEFINITIONS
const int yaw_servo_pin = 11;
const int motor_pin = 10;

const int ch1_pin = 5; // servo
const int ch2_pin = 6; // motor


// AVERAGES
const int num_readings = 10;
int readings[num_readings];
int read_index = 0;
int total = 0;
int average = 0;

Servo yaw_servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(ch1_pin, INPUT);
  pinMode(ch2_pin, INPUT);
  pinMode(motor_pin, OUTPUT);
  yaw_servo.attach(yaw_servo_pin);

  // Initialise all readings to 0
  for (int thisReading = 0; thisReading < num_readings; thisReading++) {
    readings[thisReading] = 0;
  }

  Serial.begin(9600);
}

void loop() {
  int ch1, ch2, pos;

  ch1 = pulseIn(ch1_pin, HIGH, 25000); // servo
  ch2 = pulseIn(ch2_pin, HIGH, 25000); // motor

  //print incoming messages
  Serial.print(ch1);
  Serial.print("   ");
  Serial.print(average);
  Serial.print("   ");
  Serial.println(ch2);

  delay(100);

}

void move_motor(int ch){
  //where ch = channel 2 raw input
  ch = map(ch, 1000, 1750, 0, 255);
  analogWrite(motor_pin, ch);
}

void move_servo(int ch){
  //where ch = channel 1 raw input
  int pos;
  
  // take averages.
  total = total - readings[read_index];
  readings[read_index] = ch;
  total = total + readings[read_index];
  read_index = read_index + 1; 
  if (read_index >= num_readings){
    read_index = 0;
  }
  average = total/num_readings;

  // if reciever is on, write:
  if (ch != 0) {
    pos = map(average, 1000, 2000, 10, 170);
    yaw_servo.write(pos);
  }

}


