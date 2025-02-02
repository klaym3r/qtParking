#ifndef CAR_H
#define CAR_H

#include <cmath>

class Widget;

class Car
{
public:
    Car();
    Car(double x, double y, double w, double h);

    double getX() const { return x_; }
    double getY() const { return y_; }
    double getW() const { return w_; }
    double getH() const { return h_; }
    double getCourseAngle() const { return courseAngle_; }
    double getSteeringAngle() const { return steeringAngle_; }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    void setW(double w) { w_ = w; }
    void setH(double h) { h_ = h; }
    void setCourseAngle(double angle) { courseAngle_ = angle; }
    void setSteeringAngle(double angle) { steeringAngle_ = angle; }

    void moveForward();
    void moveBackward();
    void turn();

    friend class Widget;

private:
    double x_;
    double y_;
    double w_;
    double h_;

    // r is the midpoint of the rear wheel
    double rx_;
    double ry_;

    // f is the midpoint of the front wheel
    double fx_;
    double fy_;

    // distance between r and f
    double l_;

    // angles
    double courseAngle_ = 0.0; // course angle of the car
    double steeringAngle_ = 0.0; // steering angle
    const double maxSteeringAngle_ = 35 * M_PI / 180; // 35 is average value

    // velocty
    const double velocity_ = 5.0;
};

#endif // CAR_H
