#include <Arduino.h>
#include <util/atomic.h>

const int leftEncoderPin = 2;
const int rightEncoderPin = 3;

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

int getLeftEncoderCount() {
    int leftCount;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        leftCount = leftEncoderCount;
    }
    return leftCount;
}

int getRightEncoderCount() {
    int rightCount;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        rightCount = rightEncoderCount;
    }
    return rightCount;
}


