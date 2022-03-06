
#include <Wire.h>

uint8_t b, buttonStatus[18];

void setup() {
  Serial.begin(115200);
  
  Wire.begin(); // join I2C bus (address optional for controller)
  
}


void loop() {
  // poll the I2C poeripheral for latest button status
  for (b = 0; b < 18; b++)
  {
    // send request to peripheral
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(b);              // the desired button number
    Wire.endTransmission();    // send a stop
    // request a response
    Wire.requestFrom(8, 1);    // request 1 byte from peripheral #8
    while (Wire.available()) { 
      buttonStatus[b] = (uint8_t) Wire.read(); // receive response
    }
  }

  // display the results
  Serial.println(); // blank line
  for (b = 0; b < 9; b++)
  {
    Serial.print("  ");
    Serial.print(b);
    Serial.print(": ");
    Serial.print(buttonStatus[b]);
  }
  Serial.println(); // next line
    b = 9;
    Serial.print("  ");
    Serial.print(b);
    Serial.print(": ");
    Serial.print(buttonStatus[b]);
  
  for (b = 10; b < 18; b++)
  {
    Serial.print(" ");
    Serial.print(b);
    Serial.print(": ");
    Serial.print(buttonStatus[b]);
  }

  delay(100);
}
