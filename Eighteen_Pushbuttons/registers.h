/*
 * registers on the ATmega328P
 * struct overlay of registers
 * is thanks to Tom Almy's book, "Far Inside The Arduino"
 *
 * See discussion that follows regACSR
 * for an explanation.
 */

#ifndef REGISTERS_H
#define REGISTERS_H

struct regPRR {
  // PRR register at 9.11.3 pg 38
  uint8_t pradc:1;    // Bit 0 - PRADC: Power Reduction ADC
  uint8_t prusart0:1; // Bit 1 - PRUSART0: Power Reduction USART0
  uint8_t prspi:1;    // Bit 2 - PRSPI: Power Reduction Serial Peripheral Interface
  uint8_t prtim1:1;   // Bit 3 - PRTIM1: Power Reduction Timer/Counter1
  uint8_t reserved:1; // Bit 4 - Res: Reserved bit will always read as zero
  uint8_t prtim0:1;   // Bit 5 - PRTIM0: Power Reduction Timer/Counter0
  uint8_t prtim2:1;   // Bit 6 - PRTIM2: Power Reduction Timer/Counter2
  uint8_t prtwi:1;    // Bit 7 - PRTWI: Power Reduction TWI
};
#define prr (*(volatile regPRR *)(&PRR))

struct regADCSRA {
  // ADCSRA register at 23.9.2 pg 218
  uint8_t adps:3;   // Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits pg 219
  uint8_t adie:1;   // Bit 3 – ADIE: ADC Interrupt Enable
  uint8_t adif:1;   // Bit 4 – ADIF: ADC Interrupt Flag
  uint8_t adate:1;  // Bit 5 – ADATE: ADC Auto Trigger Enable
  uint8_t adsc:1;   // Bit 6 – ADSC: ADC Start Conversion
  uint8_t aden:1;   // Bit 7 – ADEN: ADC Enable see pg 202
};
#define adcsra (*(volatile regADCSRA *)(&ADCSRA))

struct regADCSRB {
  // ADCSRB register at 23.9.4 pg 220
  uint8_t adts:3;       // Bit 2:0 – ADTS2:0: ADC Auto Trigger Source
  uint8_t reserved35:3; // Bit 5:3 Reserved
                        // To ensure compatibility with future devices, 
                        // bits 3..5 must be written to zero 
                        // when ADCSRB is written.
  uint8_t acme:1;       // Bit 6 - ACME: Analog Comparator Multiplexor Enable see pg 202
  uint8_t reserved7:1;  // Bit 7 Reserved
                        // To ensure compatibility with future devices, 
                        // bit 7 must be written to zero 
                        // when ADCSRB is written.
};
#define adcsrb (*(volatile regADCSRB *)(&ADCSRB))

struct regACSR {
  // register ACSR at 22.3.2 pg 203
  uint8_t acis:2; // Bits 1, 0 – ACIS1, ACIS0: Analog Comparator Interrupt Mode Select
  uint8_t acic:1; // Bit 2 – ACIC: Analog Comparator Input Capture Enable
  uint8_t acie:1; // Bit 3 – ACIE: Analog Comparator Interrupt Enable
  uint8_t aci:1; // Bit 4 – ACI: Analog Comparator Interrupt Flag
  uint8_t aco:1; // Bit 5 – ACO: Analog Comparator Output
  uint8_t acbg:1; // Bit 6 – ACBG: Analog Comparator Bandgap Select
  uint8_t acd:1; // Bit 7 – ACD: Analog Comparator Disable
 };
// How to access the ACSR register as a struct
// rather than as a byte?
// The #define below institutes the following steps:
// step 1 declare a struct pointer of type regACSR,
// enclosed in parentheses:
//    (volatile regACSR *)
// step 2 assign to it the address of the ACSR register,
// again using parentheses:
//    (volatile regACSR *)(&ACSR)
// step 3 place a dereference operator ("*") 
// in front of the pointer:
//    *(volatile regACSR *)(&ACSR)
// step 4 enclose the entire expression in parentheses
//    (*(volatile regACSR *)(&ACSR))
// step 5 #define the enclosed expression to be 
// the replacement for the macro "acsr".

#define acsr (*(volatile regACSR *)(&ACSR))

// We can use the dot operator
// with this acsr macro, e.g., acsr.aco,
// rather than the arrow operator, e.g. acsr->aco,
// because the dereference operator in the macro definition 
// exposes the struct to which the pointer points.

// The structs defined above are used by 
// the functions defined in registers.cpp
// that are prototyped below:

// function prototypes defined in registers.cpp 
char bitChar(byte * regAddress, byte bitNumber);
void activateAnalogComparator();

#endif
