/*
 * Eighteen Buttons
 * Version 3.0
 * David Sparks
 * March 6, 2022
 * 
 * Firmware for an I2C pushbutton peripheral
 * mounting an ATmega328p microprocessor (MPU)
 * on an Arduino Nano development board
 * managing 18 discrete, momentary pushbuttons.
 * 
 * The peripheral hardware prototype connects buttons
 * to pins 2..13 and A0..A3, A6..A7 on the Nano.
 * External 10k pull-ups are provided to pins 13, A6 and A7.
 *  
 * Pins 0, 1, A4 and A5 are reserved for communications.
 * 
 * This major code version institutes a PushButton object
 * and manages physical buttons as an array of the objects.
 * 
 * The code avoids using Arduino library functions
 * to manage and sense the pins.
 * Instead, the code directly accesses the relevant
 * I/O registers on the MPU.

 * The Analog Comparator circuit in the 328P microprocessor
 * is used to obtain digital readings from pins A6 and A7.
 * 
 * The other pins are evaluated by reading their
 * respective bits in the 328P's PINx registers.
 * 
 * PushButton.h defines descriptive macro names for
 * the register and bit location numbers of the pins
 * 
 * The main loop polls and debounces the Arudino pins 
 * that are connected to pushbuttons.
 * 
 * The I2C interface is very simple:
 *   I2C Controller sends one byte in the range 0..17
 *   specifying an index into the button array.
 *   The Peripheral returns the value obtained
 *   by the corresponding object's getBit() method.
 *   
 */

#include <Wire.h>
#include "AnalogComparator.h"
#include "PushButton.h"

// define buffer to hold 18 pushbutton objects
PushButton button[18];

// store the requested button number from I2C globally
volatile uint8_t buttonRequested;

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

  // set Analog Comparator to sense pin A6
  ADMUX = (ADMUX & 0b11111000) + 6;
  
  // do some digital pins while the analog comparator settles down
  // digital pin 2
  button[0].debounce( D_PIN_2 );
  // digital pin 3
  button[1].debounce( D_PIN_3 );
  // digital pin 4
  button[2].debounce( D_PIN_4 );
  // digital pin 5
  button[3].debounce( D_PIN_5 );
  // digital pin 6
  button[4].debounce( D_PIN_6 );
  // digital pin 7
  button[5].debounce( D_PIN_7 );

  // test Analog Comparison output for pin A6
  button[16].debounce( A_PIN_A6 );
  
  // set Analog Comparator to sense pin A7
  ADMUX = (ADMUX & 0b11111000) + 7;  
  // do the rest of the digital pins
  // while the Analog Comparator settles down

  // digital pin 8
  button[6].debounce( D_PIN_8 );
  // digital pin 9
  button[7].debounce( D_PIN_9 );
  // digital pin 10
  button[8].debounce( D_PIN_10 );
  // digital pin 11
  button[9].debounce( D_PIN_11 );
  // digital pin 12
  button[10].debounce( D_PIN_12 );
  // digital pin 13
  button[11].debounce( D_PIN_13 );
  // digital pin A0
  button[12].debounce( D_PIN_A0 );
  // digital pin A1
  button[13].debounce( D_PIN_A1 );
  // digital pin A2
  button[14].debounce( D_PIN_A2 );
  // digital pin A3
  button[15].debounce( D_PIN_A3 );

  // test Analog Comparison output for pin A7
  button[17].debounce( A_PIN_A7);
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
  // return the settled bit value
  Wire.write(button[buttonRequested].getBit());
}
