#include <iostream>
#include <string>
using namespace std;

class Coach {
public:
    int coachNumber;
    int availableSeats;
    Coach* prev;
    Coach* next;

    Coach(int number, int seats) : coachNumber(number), availableSeats(seats), prev(nullptr), next(nullptr) {}
};

class Train {
    Coach* head;
    Coach* tail;

public:
    Train() : head(nullptr), tail(nullptr) {}

    void addCoach(int coachNumber, int seats) {
        Coach* newCoach = new Coach(coachNumber, seats);
        if (!head) {
            head = newCoach;
            tail = newCoach;
        } else {
            tail->next = newCoach;
            newCoach->prev = tail;
            tail = newCoach;
        }
        cout << "Added Coach " << coachNumber << " with " << seats << " seats." << endl;
    }

    void displayCoaches() {
        Coach* current = head;
        cout << "Train Coaches:\n";
        while (current) {
            cout << "Coach " << current->coachNumber << ": " << current->availableSeats << " seats available." << endl;
            current = current->next;
        }
    }

    void removeCoach(int coachNumber) {
        Coach* current = head;
        while (current && current->coachNumber != coachNumber) {
            current = current->next;
        }
        if (!current) {
            cout << "Coach not found." << endl;
            return;
        }

        if (current == head) {
            head = current->next;
        }
        if (current == tail) {
            tail = current->prev;
        }
        if (current->prev) {
            current->prev->next = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }
        delete current;
        cout << "Removed Coach " << coachNumber << endl;
    }

    void nextCoach() {
        if (head && head->next) {
            head = head->next;
            cout << "Moved to Coach " << head->coachNumber << endl;
        } else {
            cout << "No next coach." << endl;
        }
    }

    void prevCoach() {
        if (head && head->prev) {
            head = head->prev;
            cout << "Moved to Coach " << head->coachNumber << endl;
        } else {
            cout << "No previous coach." << endl;
        }
    }
};

int main() {
    Train train;
    train.addCoach(101, 40);
    train.addCoach(102, 35);
    train.addCoach(103, 50);

    train.displayCoaches();

    train.nextCoach();  // Moves to the next coach
    train.prevCoach();  // Moves back to the previous coach

    train.removeCoach(102); // Removes a coach

    train.displayCoaches(); // Displays the current list of coaches

    return 0;
}
