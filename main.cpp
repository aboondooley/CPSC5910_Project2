#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Book.h"

using namespace std;

/*
 * Asks the user for the filepath to the books file.
 * Creates a Book object and adds each BookLog to the Book object as it reads
 * in from the file and prints out each BookLog in the Book object.
 * Then tests for shallow copies in the both copy constructor and assignment
 * operator methods. Tests the lookUpBookId and resize methods.
 * Deallocation happens automatically with the Book dtor.
 *
 * @return 0
 */

/**
 * Tests addNewBook. Reads in a file and then adds a new book for each line
 * in the file.
 * @param filename full path of the file with books
 * @param book a book object where you will store each individual BookLog
 */
void readInBooks(string filename, Book &book) {
    int b_count = 0;
    string line, author, title, year;
    ifstream inFile;
    inFile.open(filename);

    if (inFile) {
        while (getline(inFile, line)) {
            istringstream line_part(line);
            // check to make sure all three fields are present
            int c = 0;
            if (getline(line_part, author, ',')) c++;
            if (getline(line_part, title, ',')) c++;
            if (getline(line_part, year, ',')) c++;
            if (c == 3) {
                book.addNewBook(++b_count, author, title, year);
            } else {
                cout << "Author, title, or year is missing, skipping line."
                     << endl;
            }

        }
    } else {
        cout << "Error! File not found." << endl;
    }

}

/**
 * Tests out copy ctor and assignment operator
 * to make sure a shallow copy is not made
 * @param title string that you want the test to be called
 * @param original the original Book which you will copy
 * @param newBook a copy of the original book
 * @param newISBN the next ISBN for a new BookLog
 * @param newAuthor a new author for the new BookLog
 * @param newTitle a new title for the new BookLog
 * @param newYear a new year for the new BookLog
 */
void testForShallowCopies(string title, Book &original, Book &newBook, int
newISBN, string newAuthor, string newTitle, string newYear) {
    int id = newBook.addNewBook(newISBN, newAuthor, newTitle, newYear);
    cout << title << "Newly added book, newBook[id] = ";
    newBook.printBook(id);
    cout << "Does it exist in the original? original[id] = ";
    original.printBook(id);
    cout << " (expect does not exist)" << endl;
    cout << "Compare sizes: New Book size: " << newBook.size()
         << ", Original book size: " << original.size()
         << " (expect one less in "
            "Original)" << endl;
    cout << endl;
}

/**
 * Test that we can look up the BookId using the ISBN
 * @param title string that you want the test to be called
 * @param b a book reference (book array) that we can look up a BookId for
 * @param isbn the ISBN of the book we would like to get the BookId for
 */
void testLookUpBookId(string title, Book &b, int isbn) {
    int id = b.lookUpBookId(isbn);
    cout << title << "ISBN = " << isbn << " for book: ";
    b.printBook(id);
    cout << " Book Id = " << id;
    if (isbn > b.size() || isbn < 1) {
        cout << " (expect -1, does not exist) " << endl;
    } else {
        cout << " (expect one less than ISBN)" << endl;
    }
    cout << endl;
}

/**
 * Tests the resize() method by testing that we can exceed the initial capacity
 * Adds the same book over and over (for ease) until we have exceeded the
 * initial capacity, then checks to see that the size has increased past the
 * initial capacity and that we can print out the last book.
 * @param b a Book object to resize
 */
void testResize(string title, Book &b) {
    int c = Book::I_CAPACITY;
    while (c >= b.size()) {
        // add same book, for ease
        b.addNewBook(b.size() + 1, "Celeste Ng",
                     "Little Fires Everywhere", "2017");
    }
    cout << title << "Initial capacity = " << c << ", current size = "
         << b.size() << " (expect current size > initial capacity)" << endl;
    cout << "Can we print out the last book? b.printBook(b.size()-1) = ";
    b.printBook(b.size() - 1);
    cout << " (expect book to print)" << endl;
    cout << endl;
}

/**
 * Main entry point for testing all functions in Book class.
 * @return 0
 */
int main() {
    string filename;
    cout << "Enter rating file: ";
    cin >> filename;
    cout << endl;

    Book books; // tests ctor
    readInBooks(filename, books);


    // number of books and members:
    cout << "# of books: " << books.size() << endl;
    cout << endl;

    for (int i = 0; i < books.size(); i++) {
        books.printBook(i); // tests printBook()
    }
    cout << endl;

    Book newBook(books);
    int newISBN = books.size() + 1;
    string newAuthor = "Ta-Nehisi Coates";
    string newTitle = "Between the World Me";
    string newYear = "2015";

    // Test the copy ctor to make sure a shallow copy is not made
    testForShallowCopies("test copyCtor: ", books, newBook,
                         newISBN, newAuthor, newTitle, newYear);

    // Test the assignment operator to make a shallow copy is not made
    Book assignBook = newBook;
    int nISBN = newBook.size() + 1;
    string nAuthor = "Brit Bennett", nTitle = "The Vanishing Half";
    string nYear = "2020";
    testForShallowCopies("test assignment operator: ", newBook,
                         assignBook, nISBN, nAuthor, nTitle, nYear);

    // Test to make sure the book ID can be found using the ISBN
    testLookUpBookId("test lookUpBookId: ", assignBook, nISBN);
    testLookUpBookId("test BookId does not exist: ",
                     assignBook, 60);
    testLookUpBookId("test BookId is zero (does not exist): ",
                     assignBook, 0);

    // Test resize method (tests that we can exceed the initial capacity)
    testResize("test exceed initial capacity: ", assignBook);

    return 0;
}