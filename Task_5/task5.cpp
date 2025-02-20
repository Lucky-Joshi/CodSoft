#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;
};

struct Borrower {
    string name;
    string borrowerID;
};

struct Transaction {
    string borrowerID;
    string ISBN;
    time_t checkoutDate;
    time_t returnDate;
    bool isReturned;
};

class Library {
private:
    unordered_map<string, Book> books;
    unordered_map<string, Borrower> borrowers;
    vector<Transaction> transactions;

public:
    void addBook(const Book& book) {
        books[book.ISBN] = book;
    }

    void addBorrower(const Borrower& borrower) {
        borrowers[borrower.borrowerID] = borrower;
    }

    void searchBookByTitle(const string& title) {
        for (const auto& pair : books) {
            if (pair.second.title == title) {
                cout << "Found book: " << pair.second.title << " by " << pair.second.author << endl;
                return;
            }
        }
        cout << "Book not found" << endl;
    }

    void searchBookByAuthor(const string& author) {
        for (const auto& pair : books) {
            if (pair.second.author == author) {
                cout << "Found book: " << pair.second.title << " by " << pair.second.author << endl;
                return;
            }
        }
        cout << "Book not found" << endl;
    }

    void searchBookByISBN(const string& ISBN) {
        if (books.find(ISBN) != books.end()) {
            cout << "Found book: " << books[ISBN].title << " by " << books[ISBN].author << endl;
        } else {
            cout << "Book not found" << endl;
        }
    }

    void checkoutBook(const string& borrowerID, const string& ISBN) {
        if (books.find(ISBN) != books.end() && books[ISBN].isAvailable) {
            books[ISBN].isAvailable = false;
            Transaction transaction = {borrowerID, ISBN, time(0), 0, false};
            transactions.push_back(transaction);
            cout << "Book checked out successfully" << endl;
        } else {
            cout << "Book is not available" << endl;
        }
    }

    void returnBook(const string& borrowerID, const string& ISBN) {
        for (auto& transaction : transactions) {
            if (transaction.borrowerID == borrowerID && transaction.ISBN == ISBN && !transaction.isReturned) {
                transaction.isReturned = true;
                transaction.returnDate = time(0);
                books[ISBN].isAvailable = true;
                cout << "Book returned successfully" << endl;
                return;
            }
        }
        cout << "Transaction not found" << endl;
    }

    void calculateFine(const string& borrowerID, const string& ISBN) {
        for (const auto& transaction : transactions) {
            if (transaction.borrowerID == borrowerID && transaction.ISBN == ISBN && transaction.isReturned) {
                time_t now = time(0);
                double seconds = difftime(now, transaction.checkoutDate);
                int days = seconds / (60 * 60 * 24);
                if (days > 14) {
                    double fine = (days - 14) * 0.5; // Assuming $0.5 fine per day after 14 days
                    cout << "Fine for overdue book: $" << fine << endl;
                } else {
                    cout << "No fine" << endl;
                }
                return;
            }
        }
        cout << "Transaction not found" << endl;
    }

    void displayAllBooks() {
        cout << "All books in the library:" << endl;
        for (const auto& pair : books) {
            cout << "Title: " << pair.second.title << ", Author: " << pair.second.author << ", ISBN: " << pair.second.ISBN << ", Available: " << (pair.second.isAvailable ? "Yes" : "No") << endl;
        }
    }

    void displayAllBorrowers() {
        cout << "All borrowers:" << endl;
        for (const auto& pair : borrowers) {
            cout << "Name: " << pair.second.name << ", Borrower ID: " << pair.second.borrowerID << endl;
        }
    }

    void displayAllTransactions() {
        cout << "All transactions:" << endl;
        for (const auto& transaction : transactions) {
            cout << "Borrower ID: " << transaction.borrowerID << ", ISBN: " << transaction.ISBN << ", Checkout Date: " << ctime(&transaction.checkoutDate) << ", Return Date: " << (transaction.isReturned ? ctime(&transaction.returnDate) : "Not returned yet") << endl;
        }
    }
};

int main() {
    Library library;

    // Add books
    library.addBook({"The Great Gatsby", "F. Scott Fitzgerald", "1234567890", true});
    library.addBook({"1984", "George Orwell", "0987654321", true});

    // Add borrowers
    library.addBorrower({"John Doe", "B001"});
    library.addBorrower({"Jane Smith", "B002"});

    // User interface
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add Borrower\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. Search Book by ISBN\n";
        cout << "6. Checkout Book\n";
        cout << "7. Return Book\n";
        cout << "8. Calculate Fine\n";
        cout << "9. Display All Books\n";
        cout << "10. Display All Borrowers\n";
        cout << "11. Display All Transactions\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string title, author, ISBN, borrowerID, name;
        switch (choice) {
            case 1:
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter ISBN: ";
                getline(cin, ISBN);
                library.addBook({title, author, ISBN, true});
                break;
            case 2:
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter borrower ID: ";
                getline(cin, borrowerID);
                library.addBorrower({name, borrowerID});
                break;
            case 3:
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                library.searchBookByTitle(title);
                break;
            case 4:
                cout << "Enter author: ";
                cin.ignore();
                getline(cin, author);
                library.searchBookByAuthor(author);
                break;
            case 5:
                cout << "Enter ISBN: ";
                cin.ignore();
                getline(cin, ISBN);
                library.searchBookByISBN(ISBN);
                break;
            case 6:
                cout << "Enter borrower ID: ";
                cin.ignore();
                getline(cin, borrowerID);
                cout << "Enter ISBN: ";
                getline(cin, ISBN);
                library.checkoutBook(borrowerID, ISBN);
                break;
            case 7:
                cout << "Enter borrower ID: ";
                cin.ignore();
                getline(cin, borrowerID);
                cout << "Enter ISBN: ";
                getline(cin, ISBN);
                library.returnBook(borrowerID, ISBN);
                break;
            case 8:
                cout << "Enter borrower ID: ";
                cin.ignore();
                getline(cin, borrowerID);
                cout << "Enter ISBN: ";
                getline(cin, ISBN);
                library.calculateFine(borrowerID, ISBN);
                break;
            case 9:
                library.displayAllBooks();
                break;
            case 10:
                library.displayAllBorrowers();
                break;
            case 11:
                library.displayAllTransactions();
                break;
            case 12:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}
