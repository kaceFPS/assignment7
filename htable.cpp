#include <fstream>
#include "htable.h"

/**
 * @brief Constructor to create an empty hash table
 * @param size The number of buckets in the hash table
 */
HashTable::HashTable(int size) : table_size(size) {
    // Initialize the hash table with empty linked lists
    table.resize(size);
}

/**
 * @brief Destructor
 */
HashTable::~HashTable() {
    // The vector destructor is automatically called
}

/**
 * @brief Get the hash key of the order
 * @return int The hashed index of the order ID
 */
int HashTable::hash(int id) {
    return id % table_size;
}

/**
 * @brief Find an order by its ID
 * @param id: the order ID
 * @param order: the reference to stored found order (if found)
 * @return true if found, false otherwise
 */
bool HashTable::findOrder(int id, Order &order) {
    int index = hash(id);
    return table[index].findOrder(id, order);
}

/**
 * @brief Insert an order into the hash table. The order ID is used as the key.
 * A order is inserted only if its ID isn't in the table
 * @return true if inserted, false otherwise
 */
bool HashTable::insertOrder(const Order& order) {
    int index = hash(order.id);
    return table[index].insertRear(order);
    
}

/**
 * @brief Load orders from a file
 * 
 * @param file_name The name of the file to load
 */
void HashTable::fillTable(string file_name) {
    // Open the file to read
    ifstream fin;
    fin.open(file_name.c_str());
    if (!fin) {
        cout << "Error opening file " << file_name << endl;
        return;
    }

    Order order;
    while (fin >> order) {
        insertOrder(order);
    }

    fin.close(); // Close the file
}

/**
 * @brief Remove an order from the hash table. The order ID is used as the key.
 *        A order is removed only if its ID is in the table
 * 
 * @param id 
 * @return true if the order is removed, false otherwise
 */
bool HashTable::removeOrder(int id) {
    int index = hash(id);
    return table[index].removeOrder(id);
}

// Display the hash table
void HashTable::printTable() {
    for (int i = 0; i < table_size; i++) {
        cout << "Bucket " << i << ": ";
        table[i].displayAll();
    }
}

/**
 * @brief Get the total number of orders in the hash table
 * 
 * @return int The number of orders in the hash table
 */
int HashTable::numOrders() const {
    int totalOrders = 0;
    for (const auto &list : table) {
        totalOrders += list.length();
    }
    return totalOrders;
}

// Update the order in the hash table
/**
 * @brief Update an order in the hash table. The order ID is used as the key.
 * 		  A order is updated only if its ID is in the table
 * @param order the new order that is used to update the old order 
 * @return true if the order is updated, false otherwise
 */
bool HashTable::updateOrder(const Order& order) {
    int index = hash(order.id);
    return table[index].updateOrder(order);
}

/**
 * @brief Rehash the hash table to a new size. The orders are rehashed to the new table
 * 
 * @param new_size The new number of buckets in the hash table
 */
void HashTable::rehash(int new_size) {
    // Save the current state of the hash table
    vector<LinkedList> oldTable = table;

    // Resize the hash table
    table_size = new_size;
    table.clear();
    table.resize(new_size);

    // Reinsert orders into the new table
    for (const auto &list : oldTable) {
        Node *current = list.getFront();
        while (current != nullptr) {
            insertOrder(current->val);
            current = current->next;
        }
    }
}