#include <iostream>
#include <string>
using namespace std;

class Song {
public:
    string title;
    Song* prev;
    Song* next;

    Song(string t) : title(t), prev(nullptr), next(nullptr) {}
};

class Playlist {
private:
    Song* current;

public:
    Playlist() : current(nullptr) {}

    void addSong(const string& title) {
        Song* newSong = new Song(title);
        if (!current) {
            current = newSong;
        } else {
            current->next = newSong;
            newSong->prev = current;
            current = newSong;
        }
        cout << "Added song: " << title << endl;
    }

    void playNext() {
        if (current && current->next) {
            current = current->next;
            cout << "Playing: " << current->title << endl;
        } else {
            cout << "No next song." << endl;
        }
    }

    void playPrevious() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Playing: " << current->title << endl;
        } else {
            cout << "No previous song." << endl;
        }
    }

    void currentSong() {
        if (current) {
            cout << "Currently playing: " << current->title << endl;
        } else {
            cout << "No song is currently playing." << endl;
        }
    }
};

int main() {
    Playlist playlist;
    playlist.addSong("Song 1");
    playlist.addSong("Song 2");
    playlist.addSong("Song 3");

    playlist.currentSong();   // Playing: Song 3
    playlist.playPrevious();  // Playing: Song 2
    playlist.playPrevious();  // Playing: Song 1
    playlist.playNext();      // Playing: Song 2

    return 0;
}
