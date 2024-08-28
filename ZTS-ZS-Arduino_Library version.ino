/*
  Version using the ModbusMaster library (slower, but can easily be adjusted to other sensors)
  
  Modbus RTU Sound pressure Sensor Renke ZTS-SZ-BZ 
  This sketch shows how to interact with a Modbus RTU (TTL) sound pressure sensor.
  It reads the sound pressure value every 125 milliseconds and outputs it to the
  serial monitor.

  Hardware: Arduino Nano.

  GND connected to GND
  +5V connected to +5V
  D8  connected to RXD
  D7  connected to TXD

  Header P9 bridged on the ZTS-module to get "fast" dB processing.
  (without that bridge, you ge a "slow" response.)
*/


#include "SoftwareSerial.h"
#include <ModbusMaster.h>
// instantiate ModbusMaster object
ModbusMaster node;

float soundPressure;
//not uesed any more:
//byte modbusTX[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A };
//byte modbusRX[16];    //Modbus buffer
int result;


SoftwareSerial SwSerial(7, 8);  // SoftwareSerial goes to D7,D8

void setup() {
  Serial.begin(9600);
  SwSerial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  node.begin(1, SwSerial);
}

void loop() {
  // send over D7 a Modbus Holding registers read request to slave id 1, for 1 register
  //SwSerial.write(modbusTX, 8);

  result = node.readInputRegisters(0x0000, 1);
  if (result == node.ku8MBSuccess)
  {
   soundPressure =  node.getResponseBuffer(0x00)/10.0f;
   Serial.print("Sound Pressure = ");
   Serial.println(soundPressure);
  }
  else 
  {
  Serial.println("Modbus Error");
  }

  delay(120);    
}
