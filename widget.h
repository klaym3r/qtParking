#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

#include "node.h"
#include "edge.h"
#include "slot.h"
#include "car.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QVector<Node> getNodes() { return nodes_; }
    QVector<Edge> getEdges() { return edges_; }

    void setWx(const int &wx) { wx_ = wx; }
    void setWy(const int &wy) { wy_ = wy; }

    int getWx() { return wx_; }
    int getWy() { return wy_; }

    void paintCenter(const int, const int)&;
    void paintNode(const Node &);
    void paintEdge(const Node &, const Node &);
    void paintSlot(const Slot &);

    friend bool fillViaFile(Widget &);
    friend bool setNodes(Widget &, const int &wx, const int &wy);
    void setSlot();
    void setCar();
    void updatePosition(const double &rx, const double &ry);
    void parking();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Node> nodes_;
    QVector<Edge> edges_;
    Slot slot_;
    Car car_;

    int wx_ = 500;
    int wy_ = 500;
};
#endif // WIDGET_H
