#ifndef SLOT_H
#define SLOT_H

class Widget;

class Slot
{
public:
    Slot();
    Slot(double x, double y, double w, double h);

    double getX() const { return x_; }
    double getY() const { return y_; }
    double getW() const { return w_; }
    double getH() const { return h_; }
    int getNum() const { return num_; }


    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    void setW(double w) { w_ = w; }
    void setH(double h) { h_ = h; }
    void setNum(int h) { h_ = h; }

    friend class Widget;

private:
    double x_;
    double y_;
    double w_;
    double h_;
    int num_;
};

#endif // SLOT_H
