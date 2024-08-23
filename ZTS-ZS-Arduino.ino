/*
  Modbus RTU Sound pressure Sensor Renke ZTS-SZ-BZ   
  This sketch shows how to interact with a Modbus RTU (TTL) sound pressure sensor.  
  It reads the sound pressure value every 125 milliseconds and outputs it to the  
  serial monitor.  

  Hardware: Arduino Nano.

  GND connected to GND  
  +5V connected to +5V  
  D8  connected to RXD  
  D7  connected to TXD  

  Header P9 bridged to get fast dB processing  
*/


#include "SoftwareSerial.h"

float soundPressure;
byte modbusTX[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A };
byte modbusRX[16];    //Modbus buffer
int rawdB;

SoftwareSerial SwSerial(7, 8);  // SoftwareSerial goes to D7,D8

void setup() {
  Serial.begin(9600);
  SwSerial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
#if defined(TERM_IS_SOFTSER)
  Serial.swap();
#endif
}

void loop() {
  // send over D7 a Modbus Holding registers read request to slave id 1, for 1 register
  SwSerial.write(modbusTX, 8);

  // read over D8 answer from Modbus, noise level (dB*10) is on byte 5 (LSB) and byte 4 (MSB)
  SwSerial.readBytes(modbusRX, 7);

  rawdB = 256 * modbusRX[3] + modbusRX[4];
  soundPressure = rawdB / 10.0;
  Serial.print("Sound Pressure = ");
  Serial.print(soundPressure);
  Serial.println(" dB");
  delay(121);
}
