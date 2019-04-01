#include "Arduino.h"
#include "Streaming.h"

class digitalSensor
{
  private:
    byte pin;
    int modeInverse;
    int previousState;
    int currentState;
    boolean hasRising;
    boolean hasChanged;

  public:
    digitalSensor(byte aPin);
    void setUp(int aModeInverse);
    int getState();
    void setPreviousState();
    int stateHasChanged();
    int stateHasRising();
};

digitalSensor::digitalSensor(byte aPin)
{
    pin = aPin;
}

void digitalSensor::setUp(int aModeInverse)
{
    if (aModeInverse == 1)
    {
        modeInverse = 1;
    }
    else
    {
        modeInverse = 0;
    }
    pinMode(pin, INPUT_PULLUP);
}

int digitalSensor::getState()
{
    if (digitalRead(pin) == HIGH)
    {
        currentState = 1;
    }
    else
    {
        currentState = 0;
    }
    if (modeInverse == 1)
    {
        if (currentState == 0)
        {
            currentState = 1;
        }
        else
        {
            currentState = 0;
        }
    }
    if (currentState == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void digitalSensor::setPreviousState()
{
    previousState = currentState;
}

int digitalSensor::stateHasChanged()
{
    if (previousState == currentState)
    {
        hasChanged = false;
        return 0;
    }
    else
    {
        hasChanged = true;
        return 1;
    }
}

int digitalSensor::stateHasRising()
{
    if (previousState == 0 && currentState == 1)
    {
        hasRising = true;
        return 1;
    }
    else
    {
        hasRising = false;
        return 0;
    }
}

class timer
{
  private:
    unsigned int delayValue;
    unsigned int delayCurrent;
    unsigned long initTime;
    unsigned long currentMillis;
    boolean end;

  public:
    timer(int aDelayValue);
    void init();
    int timeIsUp();
    int getDelay();
};

timer::timer(int aDelayValue)
{
    delayValue = aDelayValue;
}

void timer::init()
{
    end = false;
    initTime = millis();
}

int timer::timeIsUp()
{
    currentMillis = millis();
    if (currentMillis - initTime >= delayValue)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int timer::getDelay()
{
    delayCurrent = millis() - initTime;
    return delayCurrent;
}

const unsigned int timerValue = 5000;
int pinHallSensor = 2;
int c = 0;
int incomingByte = 0;
int savedState = 0;


digitalSensor aimantVitesse(5);
timer tempsVitesse(500);

void setup()
{
    pinMode(11, OUTPUT);
    analogWrite(11, 150);

    aimantVitesse.setUp(0);
    tempsVitesse.init();
    Serial.begin(9600);
}

void loop()
{
    aimantVitesse.setPreviousState();
    savedState = aimantVitesse.getState();
    // Serial << aimantVitesse.stateHasChanged() << endl;
    // send data only when you receive data:
    if (Serial.available() > 0)
    {
        String a = Serial.readString();

        Serial << a << endl;
    }

    if (!tempsVitesse.timeIsUp())
    {
        if (aimantVitesse.stateHasRising())
        {
            c++;
        }
    }
    else
    {
        tempsVitesse.init();
        Serial << c << endl;
        c = 0;
    }
    delay(2);
}
