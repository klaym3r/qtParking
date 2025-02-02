#include "node.h"

Node::Node() {}
Node::Node(int num) : num_(num) {}
Node::Node(double x, double y) : x_(x), y_(y) {}
Node::Node(double x, double y, int num, double size) : x_(x), y_(y), num_(num), size_(size) {}


void Node::setX(double x) {
    x_ = x;
}
void Node::setY(double y) {
    y_ = y;
}
void Node::setNum(int num) {
    if (num >= 0) {
        num_ = num;
    }
    else {
        throw "Num can be only > 0";
    }
}
void Node::setSize(double size) {
    if (size >= 0) {
        size_ = size;
    }
    else {
        throw "Size can be only > 0";
    }
}
