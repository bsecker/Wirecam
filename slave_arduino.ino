// -*- mode: C++ -*-
#include <SPI.h>
#include <RH_NRF24.h>
#include <SoftwareServo.h>

RH_NRF24 nrf24;

// Define Transmitter Variables
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);
uint16_t input[4] = {0};

// Define Actuation Variables
const int yaw_servo_max_speed = 2; //maximum degrees moved per clock tick
const int joystick_x_mid_point = 507;
const int joystick_y_mid_point = 521;
const int joystick_mid_buffer = 5; // "dead" range of values - right in the middle of the joystick.
int servo_pos = 89; // initial position of servo

// Define Pins
const int servo_pin = 7;

// Initialise Yaw Servo
SoftwareServo yaw_servo;

void setup(){
  Serial.begin(9600);
  if (!nrf24.init())
    Serial.println("init failed");
  // set to 2.402 GHz (channel 2), 250kbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps , RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");

  Serial.println("Initialised RF link");   
  
  yaw_servo.attach(servo_pin);

  delay(500);
  Serial.println("Initialised YAW servo");
}

void loop(){
  if (nrf24.recv(buf, &len)){
    //concatinate the incoming 8 bytes to 4 16-bit ints
    input[0] = buf[0] << 8;
    input[0] = input[0] | buf[1];
    input[1] = buf[2] << 8;
    input[1] = input[1] | buf[3];
    input[2] = buf[4] << 8;
    input[2] = input[2] | buf[5];

    // Print Serial
    Serial.print(input[0]); Serial.print(" ");
    Serial.print(input[1]); Serial.print(" ");
    Serial.print(input[2]); Serial.println(" ");
    
   // Move Servo motor
   SoftwareServo::refresh();//refreshes servo to keep them updating
   //move_servo_yaw(input[1]);
  }
}

void move_motor(int input_speed){
  // Take 0-1023 raw input and convert it to a value for the motor shield
  
  // map 0-1023 to 0-256
  int motor_speed = map(input_speed, 0, 1024, 0, 255);
}

void move_servo_yaw( int input) {
  // Take 0-1023 input from joystick and convert it into 0-180° movement for servo.
  int speed_x = 0;
  
  // Under mid point
  if (input <= joystick_x_mid_point-joystick_mid_buffer) {
    speed_x = map(input, joystick_x_mid_point-joystick_mid_buffer, 0, 0, -yaw_servo_max_speed);
  }
  // Over mid point 
  else if (input >= joystick_x_mid_point+joystick_mid_buffer) {
    speed_x = map(input, joystick_x_mid_point+joystick_mid_buffer, 1023, 0, yaw_servo_max_speed);
  }
  // at middle point, do nothing

  //Move servo
  servo_pos += speed_x;
  servo_pos = constrain( servo_pos, 15, 170);
  
  yaw_servo.write(servo_pos);
  // https://arduino-info.wikispaces.com/RadioLink-Joystick-To-Servos
}
