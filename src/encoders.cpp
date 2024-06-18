#include <Arduino.h>
#include <util/atomic.h>

const int leftEncoderPin = 2;
const int rightEncoderPin = 3;
const int countsPerWheelRot = 30 * 12; // gear ratio * encoder counts per second
const float countsToMMPerWheelRot = (2.0 * PI * 16.0) / countsPerWheelRot; // circumference / countsPerWheelRot4

volatile int leftEncoderCount = 0;
volatile int rightEncoderCount = 0;

void updateLeftEncoderCount();
void updateRightEncoderCount();

void initializeEncoders() {
    pinMode(leftEncoderPin, INPUT);
    pinMode(rightEncoderPin, INPUT);

    attachInterrupt(digitalPinToInterrupt(leftEncoderPin), updateLeftEncoderCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(rightEncoderPin), updateRightEncoderCount, CHANGE);
}

void updateLeftEncoderCount() {
    leftEncoderCount++;
}

void updateRightEncoderCount() {
    rightEncoderCount++;
}

float getLeftDistMM() {
    float leftMM;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        leftMM = leftEncoderCount * countsToMMPerWheelRot;
    }
    return leftMM;
}

float getRightDistMM() {
    float rightMM;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        rightMM = rightEncoderCount * countsToMMPerWheelRot;
    }
    return rightMM;
}


