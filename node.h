#ifndef NODE_H
#define NODE_H

#include <QVector>


class Node
{
public:
    Node();
    Node(int num);
    Node(double x, double y);
    Node(double x, double y, int num, double size);

    void setX(double);
    void setY(double);
    void setNum(int);
    void setSize(double);

    double getX() const { return x_; }
    double getY() const { return y_; }
    double getNum() const { return num_; }
    double getSize() const { return size_; }

private:

    double x_;
    double y_;
    double num_;
    double size_;
};

#endif // NODE_H
