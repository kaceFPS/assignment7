#ifndef HASHTABLE_H
#define HASHTABLE_H


#pragma once
#include <vector>
#include "linkedlist.h"

using namespace std;

class HashTable {
private:
    vector<LinkedList> table;
    int table_size;

    int hash(int id);

public:
    HashTable(int size = 23);

    ~HashTable();

    void fillTable(string file_name);

    bool findOrder(int id, Order &order);

    bool insertOrder(const Order& order);

    bool removeOrder(int id);

    bool updateOrder(const Order& order);

    void printTable();

    int numOrders() const;

    int numBuckets() const {
        return table_size;
    }

    void rehash(int new_size);
};

#endif // HASHTABLE_H