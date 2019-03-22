#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 7

int red = 0, blue = 0, green = 0, max = 0, min = 0,Red = 0, Green = 0, Blue =  0, _R = 0, _G = 0, _B = 0;

int frequency = 0;

int r_2 = 0;
int r_1 = 0;
int moyenne = 0;

void setup() {
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
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  red = pulseIn(sensorOut, LOW);
  delay(20);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  green = pulseIn(sensorOut, LOW);
  delay(20);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);
  delay(20);

  Red = map(red, 25, 72, 255, 0);
  Green = map(green, 30, 90, 255, 0);
  Blue = map(blue, 25, 70, 255, 0);

  max = max(Red, max(Green, Blue));
  min = min(Red, min(Green, Blue));

  if (max - min < 100)
  {
    max = max + (max - min)/2;
    min = min - (max - min)/2;
  }

  if (max <= 255 || min >= 0)
  {
  _R = map(Red, min, max, 0, 255);
  _G = map(Green, min, max, 0, 255);
  _B = map(Blue, min, max, 0, 255);  
  }
  
  if (max <= 50)
  {
      max = 50;
  }

  r_1 = _R;
  r_2 = r_1;

  moyenne = (_R + r_1 + r_2) / 3;


  Serial.println(moyenne);
  //Serial.print("_R = ");
  //Serial.println(_R);
  //Serial.print("   _G = ");
  //Serial.print(_G);
  //Serial.print("   _B = ");
  //Serial.println(_B);
  //Serial.print("R = ");
  //Serial.print(Red);
  //Serial.print("   G = ");
  //Serial.print(Green);
  //Serial.print("   B = ");
  //Serial.println(Blue);
  //Serial.print("r = ");
  //Serial.print(red);
  //Serial.print("   g = ");
  //Serial.print(green);
  //Serial.print("   b = ");
  //Serial.println(blue);
  //Serial.println(max);
  //Serial.println(min);
  //Serial.println();
  //Serial.println();
  
  delay(250);
}
