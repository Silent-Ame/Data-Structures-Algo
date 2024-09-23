#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int key, value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void remove(Node* node) {
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == head) head = node->next;
        if (node == tail) tail = node->prev;
    }

    void insert(Node* node) {
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
    }

public:
    LRUCache(int cap) : capacity(cap), head(nullptr), tail(nullptr) {}

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1; // Key not found
        }

        Node* node = cache[key];
        remove(node);  // Remove from its current position
        insert(node);  // Move to front (most recently used)
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
        } else if (cache.size() == capacity) {
            cache.erase(tail->key);  // Remove least recently used (tail)
            remove(tail);
        }

        Node* newNode = new Node(key, value);
        insert(newNode);
        cache[key] = newNode;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
};

int main() {
    LRUCache cache(2); // Cache with capacity of 2

    cache.put(1, 10);
    cache.put(2, 20);

    cout << cache.get(1) << endl; // 10

    cache.put(3, 30);  // Evicts key 2

    cout << cache.get(2) << endl; // -1 (not found)
    cout << cache.get(3) << endl; // 30

    return 0;
}
