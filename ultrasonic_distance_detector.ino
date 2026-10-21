// C++ code
#include <LiquidCrystal.h>

int sonicEchoPin = 2;
int sonicTrigPin = 3;

int redPin = 4;
int yellowPin = 5;
int greenPin = 6;

int buzzPin = 7;

int RS = 8;
int EN = 9;
int DB4 = 10;
int DB5 = 11;
int DB6 = 12;
int DB7 = 13;
LiquidCrystal lcd(RS,EN,DB4,DB5,DB6,DB7);
const int safeDistance = 20;
const int warningDistance = 10;

int buzzReadPin;
int pingTravelTime;
float pingTravelDistance;
float distanceToTarget;


void setup()
{
  lcd.begin(16,2);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(sonicTrigPin, OUTPUT);
  pinMode(sonicEchoPin,  INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(sonicTrigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(sonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonicTrigPin, LOW);
  pingTravelTime = pulseIn(sonicEchoPin, HIGH);
  pingTravelDistance = (1./74.)*pingTravelTime;
  distanceToTarget = pingTravelDistance/2.;
  
  if (distanceToTarget > safeDistance)
  {
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzPin, LOW);
    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.setCursor(0,1);
    lcd.print(distanceToTarget);
    lcd.print(" inches");
  }
  else if(distanceToTarget >= warningDistance)
  {
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzPin, LOW);
    lcd.setCursor(0,0);
    lcd.print("Warning! ");
    lcd.setCursor(0,1);
    lcd.print(distanceToTarget);
    lcd.print(" inches");
  }
  else
  {
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzPin, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Too close! ");
    lcd.setCursor(0,1);
    lcd.print(distanceToTarget);
    lcd.print(" inches");
  }
  Serial.println(distanceToTarget);
}