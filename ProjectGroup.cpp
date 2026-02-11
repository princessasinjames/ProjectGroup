#include <iostream>
#include <string>
using namespace std;

// ----------------------- Classes -----------------------
template <typename S>
class CirclyList; // declares CirclyList so the operating system knows it exists so it can be friends with SongNode

template <typename S>
// class for song nodes
class SongNode {
private:
    S song; // value for node
    SongNode<S>* next; // for the next item in the list

    friend class CirclyList<S>; // gives access to the CirclyList class
};

template <typename S>
// class for the circly linked list
class CirclyList {
public:
    CirclyList(); // constructor
    ~CirclyList(); // deconstructor
    bool empty() const; // returns whether the list is empty
    void advance(); // advances the cursor
    void add(const S& s); // adds after the cursor
    void remove(); // removes after cursor
    const S& back() const; // returns element at cursor
    const S& front() const; // returns element after cursor
    void print();
private:
    SongNode<S>* cursor;
};

// ----------------------- Other Classes -----------------------

template <typename S>
// class for Exceptions
class Exceptions { // for exceptions
public:
    Exceptions(const S& error) : errorMsg(error) { }
    S getError() { return errorMsg; }
private:
    S errorMsg; // error message
};

template <typename S>
// class for EmptyList exception
class EmptyList : public Exceptions<S> { // for exception caused by an empty list
public:
    EmptyList(const S& error) : Exceptions<S>(error) { }
};

// ----------------------- Function Definitions -----------------------
template <typename S>
// constructor
CirclyList<S>::CirclyList() : cursor(NULL) { }

template <typename S>
// deconstructor
CirclyList<S>::~CirclyList() {
    while (!empty()) {
        remove();
    }
}

template <typename S>
// returns whether the list is empty
bool CirclyList<S>::empty() const {
    return cursor == NULL;
}

template <typename S>
// advances the cursor
void CirclyList<S>::advance() {
    // runs when there is no cursor to advance
    if (cursor == NULL) {
        cout << "There is no cursor to advance" << endl;
        return;
    }

    cursor = cursor->next; // advances the cursor

    cout << "Cursor advanced" << endl;
}

template <typename S>
// adds after the cursor
void CirclyList<S>::add(const S& s) {
    SongNode<S>* newSong = new SongNode<S>; // creates new song node
    newSong->song = s;

    // establishes the new song as the cursor if it is the first node being added to the list
    if (cursor == NULL) {
        newSong->next = newSong;
        cursor = newSong;
    } else { // updates the next pointers to include the new song
        newSong->next = cursor->next;
        cursor->next = newSong;
    }

    cout << "Song added" << endl;
}

template <typename S>
// removes after the cursor
void CirclyList<S>::remove() {
    // runs when there is nothing to remove
    if (cursor == NULL) {
        cout << "There is no list to remove from" << endl;
        return;
    }

    SongNode<S>* old = cursor->next;

    if (old == cursor){ // removes from a one item list
        cursor = NULL;
    } else {
        cursor->next = old->next;
    }

    cout << "Song removed" << endl;

    delete old; // frees the pointer
}

template <typename S>
// returns element at cursor
const S& CirclyList<S>::back() const {
    try {
        if (cursor == nullptr)
            throw EmptyList<S>("List is empty."); // throw for when the list is empty
    } catch (EmptyList<S> ele) {
        cout << "List has no back. Try again later." << endl; // error message
    }

    string back = cursor->song;

    cout << "Back: " << back; // outputs the back

    return cursor->song;
}

template <typename S>
// returns element after cursor
const S& CirclyList<S>::front() const {
    try {
        if (cursor == nullptr)
            throw EmptyList<S>("List is empty."); // throw for when the list is empty
    } catch (EmptyList<S> ele) {
        cout << "List has no front. Try again later." << endl; // error message
    }

    string front = cursor->next->song;

    cout << "Front: " << front; // outputs the front

    return cursor->next->song;
}

template <typename S>
// prints the songs in the circly linked list
void CirclyList<S>::print() {
    SongNode<S>* front = cursor; // creates front node to move through the list
    SongNode<S>* iterator = cursor; // creates node to compare with the front node

    // runs when there is no list to print
    if (cursor == NULL) {
        cout << "There is no list to print" << endl;
        return;
    }

    // initializes variables
    front = cursor;
    iterator = cursor;
    const string iterator_song = iterator->song;

    cout << iterator_song; // prints first song

    iterator = iterator->next;

    // prints the rest of the songs
    while (iterator != front) {
        const string iterator_song = iterator->song;
        cout << iterator_song; // prints the song
        iterator = iterator->next;
    }
}

// ----------------------- Main -----------------------
int main() {
    // creates the list
    CirclyList<string> playlist;

    // creates variables
    string new_song;
    char symbol;
    char ch;
    int exit = 1;

    // the loop for the prompt
    while (exit == 1) {
        // the prompt with the functions
        cout << "--------------------------------------------" << endl
        << "Edit playlist:" << endl
        << "1- empty" << endl << "2- advance" << endl
        << "3- add" << endl << "4- remove" << endl
        << "5- back" << endl << "6- front" << endl
        << "7- print" << endl << "8- exit" << endl;
        cout << "Enter the symbol (from 1-8) of the desired function: ";
        cin >> symbol;
        cout << "--------------------------------------------" << endl;

        // switch cases for the fucntions
        switch (symbol) { // runs the empty function
            case '1':
                if (playlist.empty()) {
                    cout << "List is empty" << endl;
                }
                break;
            case '2': // runs the advance function
                playlist.advance();
                break;
            case '3': // runs the add function
                cout << "Please enter song:" << endl;
                cin.ignore();
                new_song = "";
                do { // allows the input to have multiple words separated by a space
                    ch = cin.get(); // gets characters
                    new_song += ch; // adds the characters to the new song
                } while (ch != '\n');
                playlist.add(new_song);
                break;
            case '4': // runs the remove function
                playlist.remove();
                break;
            case '5': // runs the back function
                playlist.back();
                break;
            case '6': // runs the front function
                playlist.front();
                break;
            case '7': // runs the print function
                playlist.print();
                break;
            case '8': // ends the program
                cout << "Exit successful" << endl;
                exit = 0; // ends the while loop
                break;
            default: // ends the program with an error for invalid input
                cout << "Error: invalid symbol. Try again later." << endl;
                exit = 0; // ends the while loop
                break;
        }
    }

    return 0;
}