#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string url;
    Node* prev;
    Node* next;

    Node(string u) : url(u), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
private:
    Node* current;

public:
    BrowserHistory() : current(nullptr) {}

    void visit(const string& url) {
        Node* newPage = new Node(url);
        if (current) {
            current->next = newPage;
            newPage->prev = current;
        }
        current = newPage;
        cout << "Visited: " << url << endl;
    }

    void back() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Back to: " << current->url << endl;
        } else {
            cout << "No previous page." << endl;
        }
    }

    void forward() {
        if (current && current->next) {
            current = current->next;
            cout << "Forward to: " << current->url << endl;
        } else {
            cout << "No forward page." << endl;
        }
    }
};

int main() {
    BrowserHistory history;
    history.visit("google.com");
    history.visit("youtube.com");
    history.visit("github.com");

    history.back();    // Back to: youtube.com
    history.back();    // Back to: google.com
    history.forward(); // Forward to: youtube.com

    return 0;
}
