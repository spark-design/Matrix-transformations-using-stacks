#pragma once
#include "Matrix.h"

class Node
{
    public:
        Matrix mat;
        Node *next;

        Node(Matrix data):
            mat(data), next(nullptr) {}

        Node(Matrix data, Node *next):
            mat(data), next(next){}
};