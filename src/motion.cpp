#include <Arduino.h>
#include "encoders.h"
#include "motors.h"

const float kP = 0.1;

const int turnRadius = 74; // distance from wheel to wheel in mm


void moveMM(float dist) {
    float requestedRightDist = getRightDistMM() + abs(dist);
    float requestedLeftDist = getLeftDistMM() + abs(dist);

    while (getLeftDistMM() < requestedLeftDist || getRightDistMM() < requestedRightDist) {
        float leftError = requestedLeftDist - getLeftDistMM();
        float rightError = requestedRightDist - getRightDistMM();

        float calcPIDLeft = leftError * kP;
        float calcPIDRight = rightError * kP;

        if (dist < 0) {
            setLeftPWM(-calcPIDLeft);
            setRightPWM(-calcPIDRight);
        }
        else {
            setLeftPWM(calcPIDLeft);
            setRightPWM(calcPIDRight);
        }
    }
    setLeftPWM(0);
    setRightPWM(0);
}

void turnDeg(float deg) {
    if (deg < 0) {
        float requestedWheelDistMM = (abs(deg) / 360 * 2 * PI * turnRadius) + getLeftDistMM();
        while (getLeftDistMM() < requestedWheelDistMM) {
            float error = abs(requestedWheelDistMM - getLeftDistMM());
            float calcPID = error * kP;

            setLeftPWM(calcPID);
        } 
    }
    else {
        float requestedWheelDistMM = (abs(deg) / 360 * 2 * PI * turnRadius) + getRightDistMM();
        while (getRightDistMM() < requestedWheelDistMM) {
            float error = abs(requestedWheelDistMM - getRightDistMM());
            float calcPID = error * kP;

            setRightPWM(calcPID);
        }
    }
    setLeftPWM(0);
    setRightPWM(0);
}