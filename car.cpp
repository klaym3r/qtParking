#include <algorithm>
#include <iostream>

#include "car.h"

Car::Car() {}
Car::Car(double x, double y, double w, double h, double wheelbase) : x_(x), y_(y), w_(w), h_(h), l_(wheelbase){}

void Car::setSteeringAngle(double angle) {
    steering_angle_ = std::clamp(angle, -max_steering_angle_, max_steering_angle_);
}

void Car::move() {
    if (fabs(velocity_) < 0.01) return;

    double beta = atan(l_ / (l_ / tan(steering_angle_)));
    double dx = velocity_ * cos(course_angle_ + beta);
    double dy = velocity_ * sin(course_angle_ + beta);
    double dtheta = velocity_ * sin(beta) / l_;

    rx_ += dx;
    ry_ += dy;
    course_angle_ += dtheta;


    course_angle_ = fmod(course_angle_, 2 * M_PI);

    x_ = rx_ + 0.5 * cos(course_angle_) * (l_ - w_);
    y_ = ry_ - h_ * 0.5;

    // 1
    cords_[0].setX(x_);
    cords_[0].setY(y_);

    // 2
    cords_[1].setX(x_ + w_ * cos(course_angle_));
    cords_[1].setY(y_ + w_ * sin(course_angle_));

    // 3
    cords_[2].setX(cords_[1].getX() + h_ * sin(course_angle_));
    cords_[2].setY(cords_[1].getY() + h_ * cos(course_angle_));

    // 4
    cords_[3].setX(x_ + h_ * sin(course_angle_));
    cords_[3].setY(y_ + h_ * cos(course_angle_));

    // // 1
    // cords_[0].setX(x_);
    // cords_[0].setY(y_);

    // // 2
    // cords_[1].setX(x_ + w_ * cos(course_angle_));
    // cords_[1].setY(y_ + w_ * sin(course_angle_));

    // // 3
    // cords_[2].setX(cords_[1].getX() + h_ * sin(course_angle_));
    // cords_[2].setY(cords_[1].getY() + h_ * cos(course_angle_));

    // // 4
    // cords_[3].setX(x_ + h_ * sin(course_angle_));
    // cords_[3].setY(y_ + h_ * cos(course_angle_));
}
