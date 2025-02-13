#ifndef CAR_H
#define CAR_H

#include <cmath>

#include "node.h"

class Widget;

class Car
{
public:
    Car();
    Car(double x, double y, double w, double h, double wheelbase = 0);

    double getX() const { return x_; }
    double getY() const { return y_; }
    double getW() const { return w_; }
    double getH() const { return h_; }
    double getCourseAngle() const { return course_angle_; }
    double getSteeringAngle() const { return steering_angle_; }
    double getVelocity() const { return velocity_; }
    double getMinTurnRadius() const { return l_ / tan(max_steering_angle_); }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    void setW(double w) { w_ = w; }
    void setH(double h) { h_ = h; }
    void setWheelBase(double wheelbase) { l_ = wheelbase; }
    void setSteeringAngle(double angle);
    void setVelocity(double velocity) { velocity_ = velocity; }

    void move();


    friend class Widget;

private:
    double x_, y_; // координаты отрисовки
    double rx_, ry_; // координаты задней оси
    double w_, h_;
    double l_; // длина колесной базы
    double steering_angle_ = 0;
    double course_angle_ = 0;
    double velocity_ = 0;
    const double max_steering_angle_ = 35;

    QVector<Node> cords_;
};

#endif // CAR_H
