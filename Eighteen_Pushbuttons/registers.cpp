#include <Arduino.h>
#include "registers.h"

char bitChar(byte * regAddress, byte bitNumber) {
  char bitDigit[] = {'0', '1'};
  // handle ACSR differently 
  // pin grounded > ACO = 1 = button down
  // so we use the ACO bit directly
  if (regAddress == &ACSR) {      
    if (acsr.aco) {
      return '1';
    } else {
      return '0';
    }  
  } else {
    // other pins, ground = LOW
    // so we reverse the indication 
    if (*regAddress & (1 << bitNumber)) {
      return '0';
    } else {
      return '1';
    }  
    
  }
}

void activateAnalogComparator() {
  // enable the Analogue Comparator
  // write 0 to the bit ACIE
  // in the Analogue Comparator Control and Storage Register ACSR
  // Note: use NOT-AND logic to clear the bit
  // ACSR &= ~(0x01 << ACIE);
  acsr.acie = 0;

  // Select Internal Bandgap Reference Voltage
  // write 1 to the ACBG bit
  // in the ACSR register
  // use OR logic to set the bit
  // ACSR |= (0x01 << ACBG);
  acsr.acbg = 1;
  // arbitrary pause to allow the Bandgap voltage to stabilize
  delay(100);

  // turn on the ADC by clearing bit PRADC in register PRR  
  PRR &= ~(0x01 << PRADC);

  // disable ADC using the ADC multiplexor
  // by clearing bit ADEN in register ADCSRA  
  ADCSRA &= ~(0x01 << ADEN);

  // enable the comparator to use the ADC multiplexor
  // by setting bit ACME in register ADCSRB  
  ADCSRB |= (0x01 << ACME);  
}
