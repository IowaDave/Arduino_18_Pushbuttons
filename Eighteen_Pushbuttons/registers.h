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
// step 1 declare a regACSR type of struct pointer:
//    (volatile regACSR *)
// step 2 assign to it the address of the ACSR register
//    (volatile regACSR *)(&ACSR)
// step 3 place a dereference operator ("*") in front of the pointer
//    *(volatile regACSR *)(&ACSR)
// step 4 enclose the expression in parenthesis
//    (*(volatile regACSR *)(&ACSR))
// step 5 #define the enclosed expression to be 
// the replacement for the macro "acsr".

#define acsr (*(volatile regACSR *)(&ACSR))

// We can use the dot operator
// with this acsr macro, e.g., acsr.aco,
// rather than the arrow operator, e.g. acsr->aco,
// because the dereference operator in the macro definition 
// exposes the struct to which the pointer points.
// This is used by the bitChar() funtion, declared below.

// function prototypes defined in registers.cpp 
char bitChar(byte * regAddress, byte bitNumber);
void activateAnalogComparator();

#endif
