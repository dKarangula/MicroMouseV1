#include <Arduino.h>

const int leftMotorPin = 9;
const int rightMotorPin = 10;

const int leftDirPin = 7;
const int rightDirPin = 8;

void invertLeftMotor(bool inverted);
void invertRightMotor(bool inverted);

void initializeMotors() {
    pinMode(leftMotorPin, INPUT);
    pinMode(rightMotorPin, INPUT);

    pinMode(leftDirPin, OUTPUT);
    pinMode(rightDirPin, OUTPUT);

    digitalWrite(rightDirPin, HIGH); // Set initially to high since right motor is inverted by default
}

void setLeftPWM(float pwm) {
    if (pwm < 0) {
        invertLeftMotor(true);
        pwm *= -1;  
    }
    else {
        invertLeftMotor(false);
    }

    if (pwm > 255) {
        pwm = 255;
    }
    else if (pwm < 9 && pwm > 0) {
        pwm = 9;
    }

    analogWrite(leftMotorPin, pwm);
}

void setRightPWM(float pwm) {
    if (pwm < 0) {
        invertRightMotor(true);
        pwm *= -1;
    }
    else {
        invertRightMotor(false);
    }

    // pwm can't go above 255 or else weird stuff happens
    if (pwm > 255) { 
        pwm = 255;
    }
    // Pwm value below 9 produces no movement due to friction from internal motor stuff.
    // Have to keep so that PID will still be able to micro adjust without sending a value that doesn't enable it to move
    // Can use I term in PID to help, but I is annoying and stupid.
    // Maybe feedforward with kS value can be used for getting past initial friction?
    else if (pwm < 9 && pwm > 0) { 
        pwm = 9;
    }

    analogWrite(rightMotorPin, pwm);
}

void invertLeftMotor(bool inverted) {
    if (inverted) {
        digitalWrite(leftDirPin, HIGH);
    }
    else {
        digitalWrite(leftDirPin, LOW);
    }
}

void invertRightMotor(bool inverted) {
    if (inverted) {
        digitalWrite(rightDirPin, LOW);
    }
    else {
        digitalWrite(rightDirPin, HIGH);
    }
}