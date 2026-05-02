#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
using namespace std;

// Book structure
struct Book {
    string title;
    string author;
    bool isAvailable;
};

// Library class
class Library {
private:
    unordered_map<string, Book> books; // ISBN → Book
    stack<string> borrowHistory;       // Track borrowed books
    queue<string> waitingList;         // Queue for unavailable books

public:
    // Add a book
    void addBook(string isbn, string title, string author) {
        books[isbn] = {title, author, true};
        cout << "Book added: " << title << endl;
    }

    // Borrow a book
    void borrowBook(string isbn) {
        if (books.find(isbn) != books.end()) {
            if (books[isbn].isAvailable) {
                books[isbn].isAvailable = false;
                borrowHistory.push(isbn);
                cout << "Borrowed: " << books[isbn].title << endl;
            } else {
                waitingList.push(isbn);
                cout << "Book unavailable. Added to waiting list." << endl;
            }
        } else {
            cout << "Book not found!" << endl;
        }
    }

    // Return a book
    void returnBook(string isbn) {
        if (books.find(isbn) != books.end()) {
            books[isbn].isAvailable = true;
            cout << "Returned: " << books[isbn].title << endl;

            if (!waitingList.empty()) {
                string nextUser = waitingList.front();
                waitingList.pop();
                cout << "Next user notified for book: " << books[isbn].title << endl;
            }
        }
    }

    // Show borrow history
    void showHistory() {
        stack<string> temp = borrowHistory;
        cout << "Borrow history:" << endl;
        while (!temp.empty()) {
            string isbn = temp.top();
            temp.pop();
            cout << books[isbn].title << endl;
        }
    }
};

int main() {
    Library lib;
    lib.addBook("101", "Data Structures in C++", "Mark Weiss");
    lib.addBook("102", "Algorithms", "CLRS");

    lib.borrowBook("101");
    lib.borrowBook("101"); // Goes to waiting list
    lib.returnBook("101");

    lib.showHistory();

    return 0;
}