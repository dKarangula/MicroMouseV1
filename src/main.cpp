#include <Arduino.h>


void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(26, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // log encoder
  bool leftEncoder = digitalRead(3);
  Serial.print("Left Encoder: ");
  Serial.println(leftEncoder);

  // command sequence
  analogWrite(9, 0);
  analogWrite(10, 0);  
}