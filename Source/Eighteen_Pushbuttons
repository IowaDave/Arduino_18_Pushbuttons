/*
 * Eighteen Buttons
 * Version 1.0
 * David Sparks
 * February 20, 2022
 * 
 * I am building toward an I2C pushbutton controller
 * capable of managing 18 discrete buttons
 * with a single Arduino Nano development board.
 * The controller hardware prototype connects buttons
 * to pins 2..13 and A0..A3, A6..A7 on an Arduino Nano.
 * Pins 0 and 1 are reserved, as are pins A4 and A5.
 * This first code version simply captures a button's position
 * in an array of characters, where '0' = up and '1' = down.
 * The pushbuttons may be considered as numbered sequentially
 * from 0 to 17, according to their position in the character array.
 * No attempt is made here to debounce a button
 * or to recognize a change in a button's position.
 * Those improvements are for later versions.
 * 
 * The fun thing about this code version is that it avoids
 * using Arduino library functions to manage and sense the pins.
 * Instead, the code directly accesses the relevant I/O registers
 * on the ATmega328P MPU.
 * 
 * Note: external pull-ups are provided to pins 13, A6 and A7.
 */


#define STRING_BUF_SIZE (19)

void activateAnalogComparator();

char bitString[STRING_BUF_SIZE];

char bitChar(byte * portNumber, byte pinNumber) {
  if (*portNumber & (1 << pinNumber)) {
    return '1';
  } else {
    return '0';
  }
}

void setup() {

  Serial.begin(115200); // for debugging
  
  activateAnalogComparator();

  // set digital-capable pins to INPUT
  DDRD &= ~(0b11111100); // clear bits 2..7 = pins 2..7
  DDRB &= ~(0b00111111); // clear bits 0..5 = pins 8..13
  DDRC &= ~(0b00001111); // clear bits 0..3 = pins A0..A3
  
  // turn on internal pull-ups on the digital input pins
  PORTD |= 0b11111100;
  PORTB |= 0b00111111;
  PORTC |= 0b00001111;    

  for (int i = 0; i < STRING_BUF_SIZE - 1; i++) {
    bitString[i] = '.';
  }
  bitString[STRING_BUF_SIZE - 1] = '\0';

  Serial.println();
  Serial.println(bitString);
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

  // Analog Comparison for pin A6
  if (ACSR & (0x01 << ACO)) {
    bitString[16] = '0';
  } else {
    bitString[16] = '1';
  }

  // set ADMUX to sense pin A7
  ADMUX = (ADMUX & 0b11111000) + 7;
  
  // do the rest of the digital pins
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

  // Analog Comparison for pin A7
  if (ACSR & (0x01 << ACO)) {
    bitString[17] = '0';
  } else {
    bitString[17] = '1';
  }

  Serial.println(bitString);
  
  // wait a few
  delay(20);

}

void activateAnalogComparator() {
  ACSR &= ~(0x01 << ACIE);
  ACSR |= (0x01 << ACBG);
  PRR &= ~(0x01 << PRADC);
  ADCSRA &= ~(0x01 << ADEN);
  ADCSRB |= (0x01 << ACME);  
}
