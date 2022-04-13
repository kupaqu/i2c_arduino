// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int sendTo;
int recvFrom = 0;
char myId = 1;

void receiveEvent(int howMany) {
  recvFrom = Wire.read(); // first byte is an id of sender
  
  Serial.write("sender's id: ");
  Serial.write(recvFrom + '0');
  Serial.write("\n");
  Serial.write("message: ");
  
  while (0 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }  
  Serial.println();     
}

void setup() {
  Serial.begin(9600);   
  Wire.begin(myId); // join i2c bus (address optional for master)
  Wire.onReceive(receiveEvent);
  TWAR = (1 << 1) | 1; // enables broadcasting
}

unsigned long t = millis();

void loop() {
    if (Serial.available()) { // loop through all but the last
      sendTo = Serial.read() - '0'; 

      // send to previous
      if (sendTo == 'p' - '0')
        sendTo = recvFrom;
      // send to all
      if (sendTo == 'a' - '0')
        sendTo = 0; // 0x00 address is a broadcasting addresss
      
      Serial.write("receiver's id: ");
      Serial.write(sendTo + '0');
      Serial.write("\n");
      Serial.write("message: ");
      
      Wire.beginTransmission(sendTo);
      delay(100);
      
      Serial.read(); // read the space char
      
      Wire.write(myId); // first byte in message is an id
      while (Serial.available()) {
        char c = Serial.read(); // receive byte as a character
        Serial.write(c);
        Wire.write(c);         // print the character
      }
      Wire.endTransmission(); 
    }
}
