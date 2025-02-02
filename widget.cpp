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
    // painter.setBrush(QBrush(Qt::red));
    // painter.drawRect(car_.getX() - car_.getW() / 2, car_.getY() - car_.getH() / 2, car_.getW(), car_.getH());

    // painting parking slot
    painter.setBrush(QBrush(Qt::black));
    double x = slot_.getX();
    double y = slot_.getY();
    double w = slot_.getW();
    double h = slot_.getH();
    painter.drawLine(x, y, x, y + h);
    painter.drawLine(x, y + h, x + w, y + h);
    painter.drawLine(x + w, y + h, x + w, y);

    // painting edges
    for (int i = 1; i < nodes_.size(); ++i) {
        double x1 = nodes_[i - 1].getX();
        double y1 = nodes_[i - 1].getY();

        double x2 = nodes_[i].getX();
        double y2 = nodes_[i].getY();

        painter.drawLine(x1, y1, x2, y2);
    }

    painter.end();
}

bool fillViaFile(Widget &w) {

  QFile file("/home/klaymer/qtGraph/data.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Cannot open file:" << file.errorString();
    return false;
  }

  QTextStream in(&file);
  for (int i = 0; !in.atEnd(); ++i) {
    QString line = in.readLine();
    Node n;
    try {
      n.setNum(i);
    } catch (char const *error_message) {
      qDebug() << error_message;
      return false;
    }
    w.nodes_.push_back(n);
    for (QChar ch : line) {
      if (ch.isDigit()) {
        Edge e{i, ch.digitValue()};
        w.edges_.push_back(e);
      }
    }
  }
  file.close();
  return true;
}

bool setNodes(Widget &w, const int &wx, const int &wy) {

    int s = w.nodes_.size();

    for (int i = 0; i < s; ++i) {
        double angle = 2 * M_PI * i / s;
    try {
      w.nodes_[i].setSize(wx * 0.08);
    } catch (char const *error_message) {
      qDebug() << error_message;
      return false;
    }
    w.nodes_[i].setX(wx / 2.0 + wx * 0.2 * cos(angle) - w.nodes_[i].getSize() / 2.0);
    w.nodes_[i].setY(wx / 2.0 + wy * 0.2 * sin(angle) - w.nodes_[i].getSize() / 2.0);
  }
  return true;
}

void Widget::setSlot() {

    slot_.setH(car_.getH() * 1.5);
    slot_.setW(car_.getW() * 2);

    slot_.setX(wx_ * 0.5 - slot_.getW() * 0.5);
    slot_.setY(wy_ * 0.5 - slot_.getH() * 0.5);
}

void Widget::setCar() {
    car_.x_ = slot_.x_ - car_.w_ * 1.05;
    car_.y_ = slot_.y_ - car_.h_  - wy_ * 0.01;

    car_.rx_ = car_.x_ + car_.w_ / 4.0;
    car_.ry_ = car_.y_ + car_.h_ / 2.0;
    car_.fx_ = car_.rx_ + car_.w_ / 2.0;
    car_.fy_ = car_.ry_;

    car_.l_ = car_.fx_ - car_.rx_;
}

void Widget::updatePosition(const double &rx, const double &ry) {
    Node node(rx, ry);
    nodes_.push_back(node);
}

void Widget::parking() {

    double &cw = car_.w_;
    double &cl = car_.l_;
    double &rx = car_.rx_;
    double &ry = car_.ry_;
    double &fx = car_.fx_;
    double &fy = car_.fy_;
    double &sx = slot_.x_;
    double &sy = slot_.y_;
    double &sw = slot_.w_;
    double &sh = slot_.h_;

    double min_R = cl / tan(car_.maxSteeringAngle_);


    bool isNarrowSpace = (sw - cw) < 2 * min_R;

    double alpha = atan2(sh - min_R, sw - min_R);

    fx = sx + sw;
    fy = sy;
    rx = fx + cw * 0.5;
    ry = fy;
    cl = fx - fy;


    car_.steeringAngle_ = car_.maxSteeringAngle_;
    while (car_.courseAngle_ < alpha) {
        car_.moveBackward();
        updatePosition(rx, ry);
    }

    car_.steeringAngle_ = 0.0;
    double distance_straight = sqrt(pow(sw - 2 * min_R, 2) + pow(sh, 2));
    for (int i = 0; i < distance_straight / car_.velocity_; ++i) {
        car_.moveBackward();
        updatePosition(rx, ry);
    }

    car_.steeringAngle_ = -car_.maxSteeringAngle_;
    while (car_.courseAngle_ > 0) {
        car_.moveBackward();
        updatePosition(rx, ry);
    }

    if (isNarrowSpace) {
        int max_iterations = 3;
        for (int iter = 0; iter < max_iterations; ++iter) {
            car_.steeringAngle_ = car_.maxSteeringAngle_;
            for (int i = 0; i < 5; ++i) car_.moveForward();

            car_.steeringAngle_ = -car_.maxSteeringAngle_;
            for (int i = 0; i < 5; ++i) car_.moveBackward();
        }
    }

}
