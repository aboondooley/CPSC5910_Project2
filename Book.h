//
// Created by Alie on 9/24/2020.
//

#ifndef PROJECT2_RECOMMENDATIONS_BOOK_H
#define PROJECT2_RECOMMENDATIONS_BOOK_H
#include <iostream>

/**
 * The Book class is a collection of books, or a library. Blank books can be
 * constructed using the ctor. BookLog info can be added to the collection ,
 * and copies of existing books can be made using the assignment operator or
 * copy ctor. THe user can look up the BookId with the ISBN. You can check
 * the size of the library, print out a book and the capacity of the library
 * will increase automatically.
 * ISBN is assigned to new books by incrementing the ISBN
 * number each time, which is one greater than the bookId.
 */
class Book {
public:
    static const int I_CAPACITY = 60; // initial Book capacity
    /*
     * No arg constructor
     */
    Book();
    /*
     * Constructor with author, title and year set by user
     */

    /*
     * Copy constructor
     */
    Book(const Book &other);

    /*
     * Destructor
     */
    ~Book();

    /*
     * Assignment operator overload
     */
    Book &operator=(const Book &rhs);

    /**
     * Adds a new book to the library. All three of the fields are required
     * since the librarian is required to keep track of all four fields.
     * @param isbn = the ISBN associated with the book
     * @param author = the author of the book (string)
     * @param title = the title of the book (string)
     * @param year = year that the book was written (int)
     * @return returns the BookID
     */
    int addNewBook(const int isbn, const std::string author,
                   const std::string title, const std::string year);


    /**
     * Looks up the ISBN of the book based on its BookID
     * I changed the name because it makes more sense to me that we are
     * looking up the BookId.
     * @param isbn = The ISBN associated with the book in question
     * @return BookID which is the unique ID for the book
     */
    int lookUpBookId(int isbn) const;

    /**
     * Sees how many books are in the "library" of books.
     * @return number of books in the book collection
     */
    int size() const;


    void printBook(int bookID) const;

private:
    static const int UH_OH = -1;
    int idCounter; // keeps track of what the used ids are (increments)
    int capacity; // keeps track of the capacity of the current book array
    struct BookLog {
        int isbn;
        std::string author;
        std::string title;
        std::string year;
    };
    BookLog *library; // Ann array of book instances (book logs)

    /**
     * Resizes (doubles) the list if the I_CAPACITY is exceeded.
     */
    void resize();


};


#endif //PROJECT2_RECOMMENDATIONS_BOOK_H
