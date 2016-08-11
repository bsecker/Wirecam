// -*- mode: C++ -*-

// ---- PIN DEFINITIONS ----
const int JOYSTICK_X_PIN = A2;
const int JOYSTICK_Y_PIN = A1;
const int POT_PIN        = A3;

#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect.
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}

uint8_t data[] = "  Hello World!";
int inputInt = 0;
void loop()
{
  // Send a message to nrf24_server
 
  //Read Potentiometer:
  inputInt = analogRead(POT_PIN);
  data[0] = highByte(inputInt);
  data[1] = lowByte(inputInt);
  
  //Read Joystick X
  inputInt = analogRead(JOYSTICK_X_PIN);
  data[2] = highByte(inputInt);
  data[3] = lowByte(inputInt);

  //Read Joystick Y
  inputInt = analogRead(JOYSTICK_Y_PIN);
  data[4] = highByte(inputInt);
  data[5] = lowByte(inputInt);
  
  //Send to slave
  nrf24.send(data, sizeof(data));
  Serial.println("Sent Data");
  
  //Block until transmitter is no longer sending, and error handling.
  if(!nrf24.waitPacketSent()) {
     Serial.println("Sending Failed. Chip is not in transmit mode or other transmit failure");
  }
  
  //Wait for a bit.
  delay(200);
}
