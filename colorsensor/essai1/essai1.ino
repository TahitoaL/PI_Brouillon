/* -------------------------- *\
            PI RUNBOT
Author : TahitoaL
2019
\* -------------------------- */

#include "Arduino.h"
#include "Array.h"
#include <Streaming.h>

int abba(int a, int color)
{
    int b = int(a * float(color));
    if (b > 255)
    {
        b = 255;
    }
    if (b < 0)
    {
        b = 0;
    }
    return b;
}

class Color {
    public:
        Color(int red, int green, int blue, String name);
        void setColor(int red, int green, int blue);
        int getRed();
        int getGreen();
        int getBlue();
        String getName();
        int compare(Color color);
    protected:
        int _colors[3];
        String _name;
};

Color::Color(int red, int green, int blue, String name)
{
    _colors[0] = red;
    _colors[1] = green;
    _colors[2] = blue;
    _name = name;
}

void Color::setColor(int red, int green, int blue)
{
    _colors[0] = red;
    _colors[1] = green;
    _colors[2] = blue;
}

int Color::getRed()
{
    return _colors[0];
}

int Color::getGreen()
{
    return _colors[1];
}

int Color::getBlue()
{
    return _colors[2];
}

String Color::getName()
{
    return _name;
}

int Color::compare(Color color)
{
    // return (abs(_colors[0] - color.getRed())^2) + (abs(_colors[1] - color.getGreen())^2) + (abs(_colors[2] - color.getBlue()));
    return abs(color.getRed() - _colors[0])*3 + abs(color.getGreen() - _colors[1])*3 + abs(color.getBlue() - _colors[2])*3;
}
/*
class ColorList{
    public:
        ColorList();
        void append(Color color);
        void findColor();
    protected:
        Array<Color, 20> _colorList;
};

ColorList::ColorList()
{}

void ColorList::append(Color color)
{
    _colorL ist.push_back(color);
}
*/

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
	if(currentMillis - initTime >= delayValue)
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



//Définition valeurs pin
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 7

timer timer1(2000);
timer timer2(50);

// Array<int, 3> couleurLigne = 

int _red = 0, _blue = 0, _green = 0, max = 0, min = 0, Red = 0, Green = 0, Blue = 0, _R = 0, _G = 0, _B = 0;
float a = 0;

int frequency = 0;

int referenceColorR = 239;
int referenceColorG = 145;
int referenceColorB = 14;

int ecart = 0;
int proba = 0;
boolean detectedState = false;
String detectedColor = "Auncune";
int minGap = 0;

int r_2 = 0, v_2 = 0, b_2 = 0;
int r_1 = 0, v_1 = 0, b_1 = 0;
int moyenneR = 0, moyenneV = 0, moyenneB = 0;

boolean ledState = false;
String led = "";

Color white(255, 255, 255, "Blanc");
Color black(0, 0, 0, "Noir");
Color red(255, 0, 0, "Rouge");
Color lime(0, 255, 0, "Vert citron");
Color blue(0, 0, 255, "Bleu");
Color yellow(255, 255, 0, "Jaune");
Color brown(128, 0, 0, "Marron");
Color green(0, 128, 0, "Vert");
Color olive(128, 128, 0, "Vert olive");
Color aqua(0, 255, 255, "Turquoise");
Color navy(0, 50, 128, "Blue marine");
Color fuschia(255, 0, 255, "Fuschia");
Color purple(128, 0, 128, "Violet");
Color orange(255, 165, 0, "Orange");
Color tomette(174, 74, 52, "Rouge tomette");
Color poussin(254, 227, 71, "Jaune poussin");
Color currentColor(0, 0, 0, "Couleur détectée");

void setup()
{
    pinMode(8, OUTPUT);
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);

    pinMode(11, OUTPUT);
    digitalWrite(11, HIGH);
    pinMode(12, OUTPUT);
    digitalWrite(12, HIGH);

    // Setting frequency-scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);

    timer1.init();
    timer2.init();

    Serial.begin(9600);
}

void loop()
{
    while(!timer2.timeIsUp())
    {}
    timer2.init();
    //lecture rouge
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    _red = pulseIn(sensorOut, LOW);
    delay(10);

    //lecture vert
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    _green = pulseIn(sensorOut, LOW);
    delay(10);

    //lecture blue
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    _blue = pulseIn(sensorOut, LOW);
    delay(10);

    //redressement des valeurs
    Red = map(_red, 25, 72, 255, 0);
    Green = map(_green, 30, 90, 255, 0);
    Blue = map(_blue, 25, 70, 255, 0);

    //définition valeurs max et min
    max = max(Red, max(Green, Blue));
    min = min(Red, min(Green, Blue));

    if (max - min < 100)
    {
        max = max + (max - min) / 2;
        min = min - (max - min) / 2;
    }

    //mise a l'échelle
    if (max <= 255 || min >= 0)
    {
        _R = map(Red, min, max, 0, 255);
        _G = map(Green, min, max, 0, 255);
        _B = map(Blue, min, max, 0, 255);
    }

    if (max <= 20)
    {
        max = 20;
    }

    //sauvegarde des états antérieurs
    r_1 = _R;
    r_2 = r_1;

    v_1 = _G;
    v_2 = v_1;

    b_1 = _B;
    b_2 = b_1;

    //moyennes glissantes pour lisser le signal de sortie
    moyenneR = (_R + r_1 + r_2) / 3;
    moyenneV = (_G + v_1 + v_2) / 3;
    moyenneB = (_B + b_1 + b_2) / 3;


    //calcul de l'écart entre la couleur de référence et observée
    ecart = abs(referenceColorR - moyenneR)^2 + abs(referenceColorG - moyenneV)^2 + abs(referenceColorB - moyenneB)^2;
    proba = map(ecart, 0, 3 * 255 * 4, 100, 0);
    
    //
    if (!detectedState && ecart < 60)
    {
        detectedState = true;
    }
    if (detectedState && ecart > 100)
    {
        detectedState = false;
    }

    minGap = 255*6;

    if (currentColor.compare(white) < minGap)
    {
        minGap = currentColor.compare(white);
        detectedColor = white.getName();
    }
    if (currentColor.compare(black) < minGap)
    {
        minGap = currentColor.compare(black);
        detectedColor = black.getName();
    }
    if (currentColor.compare(red) < minGap)
    {
        minGap = currentColor.compare(red);
        detectedColor = red.getName();
    }
    if (currentColor.compare(lime) < minGap)
    {
        minGap = currentColor.compare(lime);
        detectedColor = lime.getName();
    }
    if (currentColor.compare(blue) < minGap)
    {
        minGap = currentColor.compare(blue);
        detectedColor = blue.getName();
    }
    if (currentColor.compare(yellow) < minGap)
    {
        minGap = currentColor.compare(yellow);
        detectedColor = yellow.getName();
    }
    if (currentColor.compare(brown) < minGap)
    {
        minGap = currentColor.compare(brown);
        detectedColor = brown.getName();
    }
    if (currentColor.compare(green) < minGap)
    {
        minGap = currentColor.compare(green);
        detectedColor = green.getName();
    }
    if (currentColor.compare(olive) < minGap)
    {
        minGap = currentColor.compare(olive);
        detectedColor = olive.getName();
    }
    if (currentColor.compare(aqua) < minGap)
    {
        minGap = currentColor.compare(aqua);
        detectedColor = aqua.getName();
    }
    if (currentColor.compare(navy) < minGap)
    {
        minGap = currentColor.compare(navy);
        detectedColor = navy.getName();
    }
    if (currentColor.compare(fuschia) < minGap)
    {
        minGap = currentColor.compare(fuschia);
        detectedColor = fuschia.getName();
    }
    if (currentColor.compare(purple) < minGap)
    {
        minGap = currentColor.compare(purple);
        detectedColor = purple.getName();
    }
    if (currentColor.compare(orange) < minGap)
    {
        minGap = currentColor.compare(orange);
        detectedColor = orange.getName();
    }
    if (currentColor.compare(tomette) < minGap)
    {
        minGap = currentColor.compare(tomette);
        detectedColor = tomette.getName();
    }
    if (currentColor.compare(poussin) < minGap)
    {
        minGap = currentColor.compare(poussin);
        detectedColor = poussin.getName();
    }

    currentColor.setColor(moyenneR, moyenneV, moyenneB);


    // Serial << "*n " << detectedColor << endl;

    // //format rgb(r, g, b,) pour envoie via NodeJS    
    // Serial << "*c rgb(" << moyenneR << "," << moyenneV << "," << moyenneB << ")" << endl;
    // Serial << "*p " << detectedState << endl;
    if(timer1.timeIsUp())
    {
        timer1.init();
        ledState = !ledState;
        digitalWrite(8, ledState ? LOW : HIGH);
    }


    Serial << moyenneR << "," << (ledState ? "1" : "0") << endl; 
    // delay(5);
}