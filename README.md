# Arduino_18_Pushbuttons
### Manage 18 momentary pushbuttons with one Arduino Nano

![Hardware Prototype](https://github.com/IowaDave/Arduino_18_Pushbuttons/blob/e17db35a0ab9b3aec8c0797a5a2ed53ca84d4c21/Images/IMG_2666.jpg)

I am building toward an I2C pushbutton controller capable of managing 18 discrete pushbuttons with a single Arduino Nano development board.

The controller hardware prototype connects normally-open momentary pushbuttons to pins 2..13 and A0..A3, A6..A7 on an Arduino Nano, for a total of 18 pushbuttons. The Nano actually has 22 I/O pins. Four have been reserved for communications purpoes: pins 0, 1, A4 and A5. Note: external pull-ups are provided to pins 13, A6 and A7.

This first code version simply captures a button's position in an array of characters, where '0' = up and '1' = down. The pushbuttons may be considered as numbered sequentially from 0 to 17, according to their position in the character array.

No attempt is made here to debounce a button or to recognize a change in a button's position. Those improvements are for later versions.

The fun thing about this code version is that it avoids using Arduino library functions to manage and sense the pins. Instead, the code directly accesses the relevant I/O registers on the ATmega328P MPU. 

Many thanks to Tom Almy for his wonderful book, *Far Inside The Arduino*, which inspired me to approach the project at the  micontroller level. The code takes up less space in the Nano and runs faster that way.

