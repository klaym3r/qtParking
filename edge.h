#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
    Edge();
    Edge(int start, int end);

    int getStart() const { return start_; }
    int getEnd() const { return end_; }


private:

    int start_;
    int end_;
};

#endif // EDGE_H
