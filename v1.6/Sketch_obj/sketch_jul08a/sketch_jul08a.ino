#include <EEPROM.h>

struct MyObject {

  float field1;

  byte field2;

  char name[10];
};
int address = 0;
byte value;
void setup() {

  Serial.begin(9600);

  float f = 123.456f;  //Variable to store in EEPROM.

  int eeAddress = 0;   //Location we want the data to be put.

  //One simple call, with the address first and the object second.

  EEPROM.put(eeAddress, f);

  Serial.println("Written float data type!");

  /** Put is designed for use with custom structures also. **/

  //Data to store.

  MyObject customVar = {

    3.14f,

    65,

    "Working!"

  };

  eeAddress += sizeof(float); //Move address to the next byte after float 'f'.

  EEPROM.put(eeAddress, customVar);

  Serial.print("Written custom data type! \n\nView the example sketch eeprom_get to see how you can retrieve the values!");
}

void loop() {

  /* Empty loop */
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduino Duemilanove: 512 B EEPROM storage.
    - Arduino Uno:         1 kB EEPROM storage.
    - Arduino Mega:        4 kB EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  address = address + 1;
  if (address == 100) {
    address = 0;
  }

  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  delay(500);
}
