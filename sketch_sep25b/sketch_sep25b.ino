#include <Adafruit_BMP085.h>
#include <Servo.h>
#include <Wire.h>

double P01, P02, P1, P2;
bool state = HIGH;
int dead = 500;
char wer;
Adafruit_BMP085 pressure;
  

Servo servo;
Servo servo1;
double getPressure() {
  double a = 0;
  for (byte i = 0; i < 10; i++) {
    a += pressure.readPressure();
  }
  double b = a / 10;
  return b;
}

double getDefaultPress(){
  double P, p;
    for(int i = 0; i < 11; i++){
      p = getPressure();
      P += p;
      delay(50);
    }
    return P / 10;
}

void changeBMP(){
  state = !state;
  digitalWrite(4, state);
  pressure.begin();
  delay(10);
  
}
void setup(){
    Serial.begin(9600);
    pinMode(4, OUTPUT);
    changeBMP();
    P01 = getPressure();
    changeBMP();
    P02 = getPressure();
    servo.attach(9);
    servo1.attach(10);
}


void test(){
  int alpha = 0;
  servo.write(30);
  servo1.write(30);
  delay(1000);
  servo.write(150);
  servo1.write(30);
  delay(1000);
  changeBMP();
  P1 = getPressure();
  changeBMP();
  P2 = getPressure();
  servo1.write(90 + alpha);
  delay(dead);
  while((-(P1 - P01) < P2 - P02) && alpha <= 90){
    changeBMP();
    P1 = getPressure();
    changeBMP();
    P2 = getPressure();
    servo.write(90 + alpha);
    servo1.write(90 + alpha);
    delay(dead);
    alpha++;
  }
  Serial.println(alpha);
  alpha = 0;
  servo1.write(90 + alpha);
  delay(dead);
  while(-(P1 - P01) < P2 - P02 && alpha <= 90){
    changeBMP();
    P1 = getPressure();
    changeBMP();
    P2 = getPressure();
    servo.write(90 + alpha);
    servo1.write(90 - alpha);
    delay(dead);
    alpha++;
  }
  Serial.println(alpha);
}

void loop(){
    if (Serial.available() > 0){
      wer = Serial.read();
      Serial.println("Started");
      test();
      }
}
