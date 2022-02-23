#include <Arduino.h>
#include "registers.h"

char bitChar(byte * regAddress, byte bitNumber) {
  // handle ACSR differently 
  // ACSR bit ACO bit gets set to 1 (HIGH)
  // when pin is grounded,
  // so we use that bit directly, i.e., HIGH = down
  if (regAddress == &ACSR) {
    if (acsr.aco) {
      return '1';
    } else {
      return '0';
    }  
  } else {
    // on the other pins, ground = LOW
    // so we reverse the indication LOW >> HIGH
    // to indicate the button is down
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
  ACSR &= ~(0x01 << ACIE);

  // Select Internal Bandgap Reference Voltage
  // write 1 to the ACBG bit
  // in the ACSR register
  // use OR logic to set the bit
  ACSR |= (0x01 << ACBG);
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
