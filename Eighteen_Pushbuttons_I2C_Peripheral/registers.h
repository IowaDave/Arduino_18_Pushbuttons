/*
 * registers on the ATmega328P
 */

#ifndef REGISTERS_H
#define REGISTERS_H



struct regACSR {
  // struct concept for accessing bits in register ACSR
  // is thanks to Tom Almy's book, "Far Inside The Arduino"
  int acis:2; // Bits 1, 0 – ACIS1, ACIS0: Analog Comparator Interrupt Mode Select
  int acic:1; // Bit 2 – ACIC: Analog Comparator Input Capture Enable
  int acie:1; // Bit 3 – ACIE: Analog Comparator Interrupt Enable
  int aci:1; // Bit 4 – ACI: Analog Comparator Interrupt Flag
  int aco:1; // Bit 5 – ACO: Analog Comparator Output
  int acbg:1; // Bit 6 – ACBG: Analog Comparator Bandgap Select
  int acd:1; // Bit 7 – ACD: Analog Comparator Disable
 };
// How to access the ACSR register as a struct
// rather than as a byte?
// The #define below institutes the following steps:
// step 1 declare a regACSR type of struct pointer
// step 2 assign to it the address of the ACSR register
//  think of that one as the "inner pointer"
// step 3 declare a second pointer
// step 4 assign to it the address of the inner pointer
// step 5 call this second pointer by name, "acsr"
// That having been done, we can refer to the
// Analog Comparator Output bit as if it were
// an integer-type field in a struct-type variable, 
// namely, as acsr.aco.
// This is used by the bitChar() funtion, below.
#define acsr (*(volatile regACSR *)(&ACSR))

// PS I do not understand why we can use the dot operator
// with this acsr pointer, e.g., acsr.aco,
// rather than the arrow operator, e.g. acsr->aco.
// All I know at the time of writing is that
// the dot operator works.

// function prototypes defined in registers.cpp 
char bitChar(byte * regAddress, byte bitNumber);
void activateAnalogComparator();

#endif
