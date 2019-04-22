#include "Arduino.h"
#include <EEPROM.h>

void setup ()
{
    Serial.begin(9600);
    while (!Serial) {
        ;
    }
    // int f = 0;
    // EEPROM.get(0, f);
    // Serial.println(f); 
    // for (int i = 0; i < 255; i++)
        // EEPROM.write(0, 42);
    
    // Serial.print("OK");
    int value = EEPROM.read(0);
    Serial.print(value);
}

void loop()
{
}