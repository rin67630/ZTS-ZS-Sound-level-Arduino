The chinese ZTS-ZS Sound level modules are performant and of good manufacture for a very low price.  
Sourcinge e.g.: https://de.aliexpress.com/item/1005005549693626.html  
The caveat is however that they come with zero documentation.  
I finally managed to get the TTY/MODBUS processed by an Arduino Nano.  
The protocol used is a classical MODBUS protocol. Since only one single message is implemented, I could avoid using a library and am just sending a single message and fetching the two relevant signal bytes in the response without caring to verify the CRC.  That's it !
This solution uses the widely used SoftwareSerial library to send data on D8 and receive on D7.  
A second version for the ESP8266 will follow, where the serial is swapped to D7-D8 and the user communication occurs over Telnet.  
Enjoy!
