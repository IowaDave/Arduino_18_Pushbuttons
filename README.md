# Arduino_18_Pushbuttons
### Make an I2C peripheral that provides<br>18 pushbuttons to one Arduino Nano

![Hardware Prototype](https://github.com/IowaDave/Arduino_18_Pushbuttons/blob/e17db35a0ab9b3aec8c0797a5a2ed53ca84d4c21/Images/IMG_2666.jpg)

Toward building an I2C pushbutton controller capable of managing 18 discrete pushbuttons with a single Arduino Nano development board.

The controller hardware prototype connects normally-open momentary pushbuttons to pins 2..13 and A0..A3, A6..A7 on an Arduino Nano, for a total of 18 pushbuttons. Note: external pull-ups are provided to pins 13, A6 and A7.

The Nano actually has 22 I/O pins. Four have been reserved for communications purposes: pins 0, 1, A4 and A5. 

Further notes concerning the hardware prototype
* 4.7K pull-up resistors are attached to the SDA and SCL pins on the peripheral.
* Ignore the ESP8266 shown in the image, above. It was on the bench for a different experiment and photo-bombed the moment when the peripheral took its selfie.

#### How It Works Right Now
The current code version continuously updates each button's status by storing characters in an array, (a C-type string) where '0' = up and '1' = down. The pushbuttons may be considered as numbered sequentially from 0 to 17, according to their position in the character array.

An I2C controller initiates a request for the status of a pushbutton by sending an 8-bit integer in the range 0..17.

The peripheral fetches the corresponding character from the array, which will be either:
* '0' meaning the button is Up, or
* '1' meaning the button is Down.

The value of '0' is subtracted to give a boolean result of 0 or 1, which is returned to the controller.

No attempt is made in the peripheral code to debounce a button or to report a change in a button's position. Those improvements may be considered for later versions.

A fun thing about this code is that it avoids using Arduino library functions to manage and sense the pins. Instead, the code directly accesses the relevant I/O registers on the ATmega328P MPU. The code seems to take up less space in the Nano and to run faster that way.

Many thanks to Tom Almy for his wonderful book, *Far Inside The Arduino*, which inspired me to approach the project at the microcontroller level. 

