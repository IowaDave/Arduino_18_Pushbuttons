
#include <Wire.h>

uint8_t requestButton = 16;
uint8_t buttonStatus; // 1 = down, 0 = up

void setup() {
  Serial.begin(115200);
  
  Wire.begin(); // join I2C bus (address optional for controller)
  
}

// poll the peripheral for the status of button number 3

void loop() {

  // send request to peripheral
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(requestButton);              // the desired button number
  Wire.endTransmission();    // send a stop
//  delay(100); // why not?  arbitrary wait

  // request a response
  Wire.requestFrom(8, 1);    // request 1 byte from peripheral #8
  while (Wire.available()) { 
    buttonStatus = (uint8_t) Wire.read(); // receive response
  }
  Serial.print("Button ");
  Serial.print(requestButton);
  Serial.print(" is ");
  if (buttonStatus) {
    Serial.println("Down");
  } else {
    Serial.println("Up");
  }
}
