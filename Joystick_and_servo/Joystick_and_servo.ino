
#include <Servo.h>

Servo moteur;

const int X = 0;
const int Y = 1;

const int MaxReadings = 10;

int Xreadings[MaxReadings];
int XreadIndex = 0;
int Xtotal = 0;
int X_Pos = 0;

int Yreadings[MaxReadings];
int YreadIndex = 0;
int Ytotal = 0;
int Y_Pos = 0;

int Servo_Pos = 0, Pos = 0;

void Smoother(int x_pin, int y_pin)
{
  Xtotal = Xtotal - Xreadings[XreadIndex];
  Ytotal = Ytotal - Yreadings[YreadIndex];
  delay(1);
  Xreadings[XreadIndex] = analogRead(x_pin);
  Yreadings[YreadIndex] = analogRead(y_pin);
  delay(1);
  Xtotal = Xtotal + Xreadings[XreadIndex];
  Ytotal = Ytotal + Yreadings[YreadIndex];
  delay(1);
  XreadIndex = XreadIndex + 1;
  YreadIndex = YreadIndex + 1;
  if (XreadIndex >= MaxReadings) XreadIndex = 0;
  if (YreadIndex >= MaxReadings) YreadIndex = 0;
  delay(1);
  X_Pos = Xtotal / MaxReadings;
  Y_Pos = Ytotal / MaxReadings;

}


void setup() {

  Serial.begin(9600);
  moteur.attach(9);
  for (int i = 0; i < MaxReadings; i++) {
    Xreadings[i] = 0;
    Yreadings[i] = 0;
  }
}

void loop() {
  Smoother(X, Y);
  Servo_Pos = map(X_Pos, 0, 1023, 0, 180);
  moteur.write(Servo_Pos);
  Serial.println(Servo_Pos);
  delay(15);
}

