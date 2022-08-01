#include <Servo.h>

//Configration
//Pins
#define LDR1      A0
#define LDR2      A1
#define LDR3      A2
#define LDR4      A3
#define servoXpin 9
#define servoYpin 10

//Calibration for LDRs
#define NumbersOfReadins  250
#define SensTolr          20
#define Cal1              1000
#define Cal2              1020
#define Cal3              1020
#define Cal4              1020

//Angles
#define minXAngle 0
#define maxXAngle 180
#define minYAngle 75
#define maxYAngle 125


int angleX = 90;
int angleY = 100;
Servo servoX, servoY;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoX.attach(servoXpin);
  servoX.write(angleX);
  servoY.attach(servoYpin);
  servoY.write(angleY);
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(LDR4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long LDR1Value = 970, LDR2Value = 1007, LDR3Value = 1004, LDR4Value = 1009;
  //Reading teh values of the PhotoCells
  static int cont = 0;



  for (cont = 0; cont < NumbersOfReadins; cont++)
  {
    LDR1Value += analogRead(LDR1) - Cal1;
    LDR2Value += analogRead(LDR2) - Cal2;
    LDR3Value += analogRead(LDR3) - Cal3;
    LDR4Value += analogRead(LDR4) - Cal4;
  }

  LDR1Value /= NumbersOfReadins + 1;
  LDR2Value /= NumbersOfReadins + 1;
  LDR3Value /= NumbersOfReadins + 1;
  LDR4Value /= NumbersOfReadins + 1;

//  Cal1 = LDR1Value;
//  Cal2 = LDR2Value;
//  Cal3 = LDR3Value;
//  Cal4 = LDR4Value;

  Serial.println(String(LDR1Value) + "\t" + String(LDR2Value) + "\t" + String(LDR3Value) + "\t" + String(LDR4Value));
  //Calculating the diifferencea in the light intensities
  int deltaX = (LDR1Value + LDR2Value - LDR3Value - LDR4Value)/SensTolr;
  int deltaY = (LDR1Value + LDR4Value - LDR2Value - LDR3Value)/SensTolr;
  //Moving the the PhotoCells to thr the best location
  if (deltaX > 0 && angleX < maxXAngle)
  {
    angleX++;
  }
  if (deltaX < 0 && angleX > minXAngle)
  {
    angleX--;
  }
  if (deltaY < 0 && angleY < maxYAngle)
  {
    angleY++;
  }
  if (deltaY > 0 && angleY > minYAngle)
  {
    angleY--;
  }

  servoX.write(angleX);
  //Serial.println(angleY);
  servoY.write(angleY);
}
