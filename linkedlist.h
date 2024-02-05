#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#pragma once

#include <string>
#include "order.h"
using namespace std;

typedef Order T;

struct Node {
    T val;
    Node *next;

    Node(T val, Node *next = nullptr) {
        this->val = val;
        this->next = next;
    }
};

class LinkedList {
private:
    Node *front;
    Node *rear;
    int count;

public:
    LinkedList() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~LinkedList();

    LinkedList(const LinkedList &other);

    bool insertRear(const Order& order);

    LinkedList &operator=(const LinkedList &other);

    bool isEmpty() const;

    bool findOrder(int id, Order &order);

    bool updateOrder(const Order& order);

    bool removeOrder(int id);

    int length() const;

    void displayAll();

    void addFront(T val);

    void addRear(T val);

    bool deleteFront(T &val);

    bool deleteRear(T &val);

    bool deleteAt(int pos, T &val);

    bool insertAt(int pos, T val);

    int search(const T& val) const;

    Node* getNode(int pos) const {
        if (pos < 0 || pos >= count) {
            return nullptr;
        }
        Node *p = front;
        for (int i = 0; i < pos; i++) {
            p = p->next;
        }
        return p;
    }

    Node *getFront() const { return front; }

    Node *getRear() const { return rear; }
};

#endif // LINKEDLIST_H