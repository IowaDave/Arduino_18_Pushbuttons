# Arduino_18_Pushbuttons
### An I2C peripheral that provides<br>18 pushbuttons to one Arduino Nano

![Hardware Prototype](https://github.com/IowaDave/Arduino_18_Pushbuttons/blob/e17db35a0ab9b3aec8c0797a5a2ed53ca84d4c21/Images/IMG_2666.jpg)

Updated to Version 3.0 March 6, 2022

This project develops an I2C pushbutton controller managing 18 discrete pushbuttons with a single Arduino Nano development board.

The controller hardware prototype connects normally-open momentary pushbuttons to pins 2..13 and A0..A3, A6..A7 on an Arduino Nano, for a total of 18 pushbuttons. Note: external pull-ups are provided to pins 13, A6 and A7.

The Nano actually has 22 I/O pins. Four have been reserved for communications purposes: pins 0, 1, A4 and A5. 

Further notes concerning the hardware prototype
* 4.7K pull-up resistors are attached to the SDA and SCL pins on the peripheral.
* Ignore the ESP8266 shown in the image, above. It was on the bench for a different experiment and photo-bombed the moment when the peripheral took its selfie.

#### How It Works Right Now
Version 3.0 institutes a new PushButton class. Note that the header defining this class is new code by the author, not related to other PushButton libraries that might be out there somewhere in the world.

The peripheral manages the pushbuttons internally as an array of PushButton objects.

An I2C controller initiates a request for the status of a pushbutton by sending an 8-bit integer in the range 0..17. The integer will be treated as a index into the array.

The peripheral returns the value obtained from the getBit() method of the corresponding object. It, which will be either:
* 0 meaning the button is Up, or
* 1 meaning the button is Down.

The new PushButton class provides a method, debounce(), for debouncing an Arduino pin. Parameters for debounce() are the ATmega328P PINx register and the bit-position number in the register corresponding to the Arduino pin. 

Descriptively-named macros in the PushButton.h header define the register and pin number pairs for each pin.

A fun thing about this code is that it avoids using Arduino library functions to manage and sense the pins. Instead, the code directly accesses the relevant I/O registers on the ATmega328P MPU. The code seems to take up less space in the Nano and to run faster that way.

Many thanks to Tom Almy for his wonderful book, *Far Inside The Arduino*, which inspired me to approach the project at the microcontroller level. 

