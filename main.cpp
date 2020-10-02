#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Book.h"
using namespace std;

/*
 * Asks the reader for the file path to the ratings file.
 * Reads in the ratings file and creates a 1D array to keep track of the members
 * Creates a 2D array to keep track of the member's ratings of each book in
 * the library.
 * Prints out the member's name and then all of their ratings.
 *
 * Ratings:
 * -5 = Hated it!
 * -3 = Didn't like it
 * 0 = Haven't read it
 * 1 = ok - neither hot nor cold about it
 * 3 = Liked it!
 * 5 = Really liked it!
 *
 * Finally, deallocates memory from the 1D and 2D arrays.
 * @return 0
 */

/**
 * Tests addNewBook. Reads in a file and then adds a new book for each line
 * in the file.
 * @param filename full path of the file with books
 * @param book a book object where you will store each individual BookLog
 */
void readInBooks(string filename, Book &book){
    int b_count = 0;
    string line, author, title, year;
    ifstream inFile;
    inFile.open(filename);

    if (inFile){
        while (getline(inFile, line)){
            //cout << line << endl;
            istringstream line_part(line);
            // TODO create if statements to make sure all lines are there
            getline(line_part, author, ',');
            //cout << author << " ";
            getline(line_part, title, ',');
            //cout << title << " ";
            getline(line_part, year, ',');
            //cout << year << endl;
            book.addNewBook(++b_count, author, title, year);
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
newISBN, string newAuthor, string newTitle, string newYear){
    int id = newBook.addNewBook(newISBN, newAuthor, newTitle, newYear);
    cout << title << ": Newly added book, newBook[id] = ";
    newBook.printBook(id);
    cout << "Does it exist in the original? original[id] = ";
    original.printBook(id);
    cout << " (expect does not exist)" << endl;
    cout << "Compare sizes: New Book size: " << newBook.size()
    << " Original book size: " << original.size() << " (expect one less in "
     "Original)" << endl;
    cout << endl;
}

/**
 * Test that we can look up the BookId using the ISBN
 * @param title string that you want the test to be called
 * @param b a book reference (book array) that we can look up a BookId for
 * @param isbn the ISBN of the book we would like to get the BookId for
 */
void testLookUpBookId(string title, Book &b, int isbn){
    int id = b.lookUpBookId(isbn);
    cout << title << "ISBN = " << isbn << " for book: ";
    b.printBook(id);
    cout << " Book Id = " << id << " (expect one less than ISBN)" << endl;

}

/*
void testResize(){
    while ()

} */

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

    for (int i = 0; i < books.size(); i++){
        books.printBook(i); // tests printBook()
    }
    cout << endl;

    Book newBook(books);
    int newISBN = books.size()+1;
    string newAuthor = "Ta-Nehisi Coates";
    string newTitle = "Between the World Me";
    string newYear = "2015";

    // Test the copy ctor to make sure a shallow copy is not made
    testForShallowCopies("test copyCtor: ", books, newBook, newISBN, newAuthor,
               newTitle, newYear);

    // Test the assignment operator to make a shallow copy is not made
    Book assignBook = newBook;
    int nISBN = newBook.size()+1;
    string nAuthor = "Brit Bennett", nTitle = "The Vanishing Half";
    string nYear ="2020";
    testForShallowCopies("test assignment operator: ", newBook, assignBook,
                        nISBN,
               nAuthor, nTitle, nYear);

    testLookUpBookId("test lookUpBookId: ", assignBook, nISBN);




    return 0;
}