#include "Streaming.h";

void setup()
{
    Serial.begin(9600);
}

void loop()
{

    Serial << analogRead(A0) << endl;
}