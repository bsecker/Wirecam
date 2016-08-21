/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

// Define Pins
const int servo_pin = 9;
const int joystick_pin = A1;

// Create servo object to control main servo
Servo yaw_servo;  

// Define Variables
const int joystick_mid_point = 521;
const int servo_rest_pos = 89;
const int max_turn_speed = 3; 
int servo_pos = 89;    // variable to store the servo position


void setup() {
  yaw_servo.attach(servo_pin);  
  yaw_servo.write(servo_rest_pos); // set servo to middle
  pinMode(joystick_pin, INPUT);
  Serial.begin(9600);
  delay(500);
}

void loop() {
  int _joystick_val, speed_x;

  // Get joystick value
  _joystick_val = analogRead(joystick_pin);
  speed_x = 0;

  // Larger than rest position:
  if (_joystick_val >= joystick_mid_point+3) {
    speed_x = map(_joystick_val, joystick_mid_point+3, 1023, 0, max_turn_speed);
  }
  else if (_joystick_val <= joystick_mid_point-3) {
    speed_x = map(_joystick_val, joystick_mid_point-3, 0, 0, -max_turn_speed);
  }

  set_pos(speed_x);

  // Print Values
  Serial.print(_joystick_val);
  Serial.print("    ");
  Serial.println(speed_x);
}

void set_pos(int servo_speed) {
  // Take servo speed and convert to degrees, then write to servo
  servo_pos += servo_speed;
  servo_pos = constrain(servo_pos, 15, 180); // keep within bounds

  yaw_servo.write(servo_pos);
  delay(25);
}