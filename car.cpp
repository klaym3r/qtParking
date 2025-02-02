#include <cmath>

#include "car.h"

Car::Car() {}
Car::Car(double x, double y, double w, double h) : x_(x), y_(y), w_(w), h_(h) {}

double computeDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void Car::moveForward() {
    rx_ += velocity_ * cos(steeringAngle_) * cos(courseAngle_);
    ry_ += velocity_ * cos(steeringAngle_) * sin(courseAngle_);

    courseAngle_ = (velocity_ / l_) * sin(steeringAngle_);
}

void Car::moveBackward() {
    rx_ -= velocity_ * cos(steeringAngle_) * cos(courseAngle_);
    ry_ -= velocity_ * cos(steeringAngle_) * sin(courseAngle_);

    courseAngle_ = (velocity_ / l_) * sin(steeringAngle_);
}
