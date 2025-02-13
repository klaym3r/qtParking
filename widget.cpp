#include <QPainter>
#include <QPainterPath>
#include <QFile>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    car_.setW(wx_ * 0.2);
    car_.setH(wy_ * 0.1);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // painting car
    painter.setPen(QPen(Qt::red));

    for (int i = 1; i < car_.cords_.size(); ++i) {
        painter.drawLine(car_.cords_[i - 1].getX(), car_.cords_[i - 1].getY(), car_.cords_[i].getX(), car_.cords_[i].getY());
    }
    painter.drawLine(car_.cords_[0].getX(), car_.cords_[0].getY(), car_.cords_[car_.cords_.size() - 1].getX(), car_.cords_[car_.cords_.size() - 1].getY());

    // painter.drawRect(x1, y1, x2, y2);
    // painter.drawRect(, car_.y_, car_.x_ + car_.w_ * cos(car_.course_angle_), car_.y_ + car_.w_ * sin(car_.course_angle_));
    painter.setPen(QPen(Qt::black));
    painter.drawLine(car_.rx_, car_.ry_, car_.rx_ + car_.l_ * cos(car_.course_angle_), car_.ry_ + car_.l_ * sin(car_.course_angle_));


    // painting parking slot
    double x = slot_.getX();
    double y = slot_.getY();
    double w = slot_.getW();
    double h = slot_.getH();
    painter.drawLine(x, y, x, y + h);
    painter.drawLine(x, y + h, x + w, y + h);
    painter.drawLine(x + w, y + h, x + w, y);

    // painting edges
    painter.setPen(QPen(Qt::green));
    for (int i = 1; i < nodes_.size(); ++i) {
        double x1 = nodes_[i - 1].getX();
        double y1 = nodes_[i - 1].getY();

        double x2 = nodes_[i].getX();
        double y2 = nodes_[i].getY();

        painter.drawLine(x1, y1, x2, y2);
    }

    painter.end();
}

void Widget::setSlot() {

    // координаты x и y парковочного места находятся в его начальной точке отрисовки
    slot_.w_ = car_.w_ * 2.0;
    slot_.h_ = car_.h_ * 1.5;
    slot_.x_ = wx_ * 0.5 - slot_.w_;
    slot_.y_ = wy_ * 0.5;
    qDebug() << "Slot:\nx: " << slot_.x_ << "\ty: " << slot_.y_
             << "\nw: " << slot_.w_ << "\th: " << slot_.h_;
}

void Widget::setCar() {

    // инициализировать функцию только после setSlot()
    // координаты x и y парковочного места находятся в его начальной точке отрисовки
    car_.x_ = slot_.x_ + slot_.w_;
    car_.y_ = slot_.y_ - car_.h_ * 1.4;

    // распологаем заднюю ось относительно центра автомобиля и его колесной базы
    car_.l_ = car_.w_ * 0.5;
    car_.rx_ = car_.x_ + 0.5 * car_.w_ - car_.l_ * 0.5;
    car_.ry_ = car_.y_ + 0.5 * car_.h_;

    Node node;
    // 1
    node.setX(car_.x_);
    node.setY(car_.y_);
    car_.cords_.push_back(node);

    // 2
    node.setX(car_.x_ + car_.w_ * cos(car_.course_angle_));
    node.setY(car_.y_ + car_.w_ * sin(car_.course_angle_));
    car_.cords_.push_back(node);

    // 3
    node.setX(car_.cords_[1].getX() + car_.h_ * sin(car_.course_angle_));
    node.setY(car_.cords_[1].getY() + car_.h_ * cos(car_.course_angle_));
    car_.cords_.push_back(node);

    // 4
    node.setX(car_.x_ + car_.h_ * sin(car_.course_angle_));
    node.setY(car_.y_ + car_.h_ * cos(car_.course_angle_));
    car_.cords_.push_back(node);

    qDebug() << "--- start";
    qDebug() << "Car:\nx: " << car_.x_ << "\ty: " << car_.y_
             << "\nrx: " << car_.rx_ << "\try: " << car_.ry_ << "\tl: " << car_.l_
             << "\nw: " << car_.w_ << "\th: " << car_.h_;

}

void Widget::parking() {

    car_.velocity_ = -5.0;

    Node node;
    while (car_.rx_ > (slot_.x_ + slot_.w_)) {
        car_.move();
        node.setX(car_.rx_);
        node.setY(car_.ry_);
        nodes_.push_back(node);
    }

    car_.setSteeringAngle(-30);
    for (int i = 0; i < 2; ++i) {
        car_.move();
        node.setX(car_.rx_);
        node.setY(car_.ry_);
        nodes_.push_back(node);
    }



    qDebug() << Qt::endl << "--- end";
    qDebug() << "Car:\nx: " << car_.x_ << "\ty: " << car_.y_
             << "\nrx: " << car_.rx_ << "\try: " << car_.ry_ << "\tl: " << car_.l_
             << "\nw: " << car_.w_ << "\th: " << car_.h_;
}
