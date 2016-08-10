#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;

//Input vars
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);
uint16_t input[4] = {0};

void setup(){
  Serial.begin(9600);
  if (!nrf24.init())
    Serial.println("init failed");
  // set to 2.402 GHz (channel 2), 250kbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps , RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");

  Serial.println("Initialised!");   
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

    Serial.print(input[0]); Serial.print(" ");
    Serial.print(input[1]); Serial.print(" ");
    Serial.print(input[2]); Serial.println(" ");
    
    

  }
}
