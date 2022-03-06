#include <Arduino.h>
#include "AnalogComparator.h"


void activateAnalogComparator() {
  // enable the Analogue Comparator
  // five actions are required, in the following order
  
  // write 0 to the bit ACIE
  // in the Analogue Comparator Control and Storage Register ACSR
  acsr.acie = 0;

  // Select Internal Bandgap Reference Voltage
  // write 1 to the ACBG bit in the ACSR register
  acsr.acbg = 1;
  // arbitrary pause to allow the Bandgap voltage to stabilize
  delay(100);

  // turn on the ADC by clearing bit PRADC in register PRR  
  prr.pradc = 0;

  // disable ADC using the ADC multiplexor
  // by clearing bit ADEN in register ADCSRA  
  adcsra.aden = 0;

  // enable the comparator to use the ADC multiplexor
  // by setting bit ACME in register ADCSRB  
  adcsrb.acme = 1;
}
