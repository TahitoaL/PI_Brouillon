#include "Streaming.h"

int E1 = 11;
int value = 0;

void setup()
{
    pinMode(E1, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    // digitalWrite(E1, HIGH);
    // delay(2000);
    // analogWrite(E1, 255);
    // delay(2000);
    // analogWrite(E1, 240);
    // delay(2000);
    // analogWrite(E1, 200);
    // delay(2000);
    // analogWrite(E1, 130);
    // delay(2000);
    // analogWrite(E1, 65);
    // delay(2000);
    // digitalWrite(E1,LOW);
    // delay(2000);
    value = map(analogRead(A0), 0, 1023, 110, 255);
    analogWrite(E1, value  == 110 ? 0 : value);
    Serial << "valzue : " << value << endl;
    delay(5);
}