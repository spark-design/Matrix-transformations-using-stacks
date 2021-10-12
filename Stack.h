#pragma once
#include "Node.h"

class Stack
{
private:

    double cosConvert(double angle);
    double sinConvert(double angle);

public:
    Node* top;

    Stack() :
        top(nullptr) {}

    ~Stack();

    void push(Matrix data);
    bool peek(Matrix& data);
    void pitch(double angle);
    void yaw(double angle);
    void roll(double angle);
    void translate(double x, double y, double z);

    bool pop();

    void display();
    void transformVertex(double doubleArg1, double doubleArg2, double doubleArg3);
};
