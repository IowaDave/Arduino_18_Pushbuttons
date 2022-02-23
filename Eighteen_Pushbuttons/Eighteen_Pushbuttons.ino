/*
 * Eighteen Buttons
 * Version 2.0
 * David Sparks
 * February 21, 2022
 * 
 * Firmware for an I2C pushbutton peripheral
 * mounting an ATmega328p microprocessor (MPU)
 * on an Arduino Nano development board
 * managing 18 discrete, momentary pushbuttons.
 * 
 * The peripheral hardware prototype connects buttons
 * to pins 2..13 and A0..A3, A6..A7 on the Nano.
 * External 10k pull-ups are provided to pins 13, A6 and A7.
 * Pins 0, 1, A4 andc A5 are reserved for communications.
 * 
 * This code version captures a button's position
 * in an array of characters, where '0' = up and '1' = down.
 * The pushbuttons may be considered as numbered sequentially
 * from 0 to 17, according to their position in the character array.
 * No attempt is made here to debounce a button
 * or to recognize a change in a button's position.
 * Such improvements may be considerred in later versions.
 * 
 * The fun thing about this code version is that it avoids
 * using Arduino library functions to manage and sense the pins.
 * Instead, the code directly accesses the relevant I/O registers
 * on the MPU.
 * 
 * This is the first version to work with I2C.
 * It is very simple:
 *   I2C Controller sends one byte in the range 0..17
 *   specifying a position in the charqcter array.
 *   The character there will be either '0' or '1'.
 *   
 * 
 */

#include <Wire.h>
#include "registers.h"

// define buffer to hold 18 pin status chars
// where '0' = button is up,
// and '1' = button is down.
// Array position = pushbutton number:
//                  0         1
//                  012345678901234567
char bitString[] = "000000000000000000";

// store the requested button number globally
uint8_t buttonRequested;

// I2C event handler prototypes
void receiveEvent(int howMany);
void requestEvent();

void setup() {

  Wire.begin(8); // Become an I2C peripheral at address 8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  
  activateAnalogComparator();

  // set digital-capable pins to INPUT
  DDRD &= ~(0b11111100); // clear bits 2..7 = pins 2..7
  DDRB &= ~(0b00111111); // clear bits 0..5 = pins 8..13
  DDRC &= ~(0b00001111); // clear bits 0..3 = pins A0..A3
  
  // turn on internal pull-ups on the digital input pins
  PORTD |= 0b11111100;
  PORTB |= 0b00111111;
  PORTC |= 0b00001111;    

}

void loop() {

  // set ADMUX to sense pin A6
  ADMUX = (ADMUX & 0b11111000) + 6;
  // do some digital pins while the analog comparator settles down

  // digital pin 2
  bitString[0] = bitChar(&PIND, PIND2);
  // digital pin 3
  bitString[1] = bitChar(&PIND, PIND3);
  // digital pin 4
  bitString[2] = bitChar(&PIND, PIND4);
  // digital pin 5
  bitString[3] = bitChar(&PIND, PIND5);
  // digital pin 6
  bitString[4] = bitChar(&PIND, PIND6);
  // digital pin 7
  bitString[5] = bitChar(&PIND, PIND7);

  // test Analog Comparison output for pin A6
  bitString[16] = bitChar(&ACSR, ACO);
  // set ADMUX to sense pin A7
  ADMUX = (ADMUX & 0b11111000) + 7;  
  // do the rest of the digital pins
  // while the Analog Comparator settles down

  // digital pin 8
  bitString[6] = bitChar(&PINB, PINB0);
  // digital pin 9
  bitString[7] = bitChar(&PINB, PINB1);
  // digital pin 10
  bitString[8] = bitChar(&PINB, PINB2);
  // digital pin 11
  bitString[9] = bitChar(&PINB, PINB3);
  // digital pin 12
  bitString[10] = bitChar(&PINB, PINB4);
  // digital pin 13
  bitString[11] = bitChar(&PINB, PINB5);
  // digital pin A0
  bitString[12] = bitChar(&PINC, PINC0);
  // digital pin A1
  bitString[13] = bitChar(&PINC, PINC1);
  // digital pin A2
  bitString[14] = bitChar(&PINC, PINC2);
  // digital pin A3
  bitString[15] = bitChar(&PINC, PINC3);

  // test Analog Comparison output for pin A7
  bitString[17] = bitChar(&ACSR, ACO);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { 
    // loop through all but the final
    // however, we're getting only 1 byte
    // so I expect this block to be skipped
    buttonRequested = (uint8_t) Wire.read(); // receive byte as a uint8_t
  }
  buttonRequested = (uint8_t) Wire.read();    // receive byte as uint8_t
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  // bitString holds chars, '0' or '1'. 
  // Subtract '0' to convert to uint8_t 0 or 1.
  Wire.write(bitString[buttonRequested] - '0'); // respond with pin status
  // in one byte as expected by controller
}
