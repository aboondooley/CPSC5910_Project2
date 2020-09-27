//
// Created by Alie on 9/24/2020.
//

#ifndef PROJECT2_RECOMMENDATIONS_BOOK_H
#define PROJECT2_RECOMMENDATIONS_BOOK_H
#include <iostream>

/**
 * The Book class is a collection of books, a library, if you will. Members
 * can log in, add a new book to the library, and also rate a book that they
 * have read.
 * It also assigns ISBN to new books by incrementing the ISBN
 * number each time.
 */
class Book {
public:
    /**
     * Adds a new book to the library. All three of the fields are required
     * since the librarian is required to keep track of all four fields.
     * @param author = the author of the book (string)
     * @param title = the title of the book (string)
     * @param year = year that the book was written (int)
     * @return 0 to signal signal success and -1 to signal that the book
     * already exists
     */
    int addNewBook(std::string author, std::string title, int year);

    /**
     * Allows the member to rate a particular book. The member must know the
     * name of the member as well as the author and book name, and year.
     * @param member = the name of the member who is rating the book (string)
     * @param author = name of the author of the book (string)
     * @param title = title of the book (string)
     * @param year = year that the book was written (int)
     * @return 0 if the rating was successful and -1 if the book or member
     * do not exist
     */
    int rateBook(std::string member, std::string author, std::string title, int
    year);
    /**
     * Again, allows the member to rate a particular book. The member must know
     * the account number of the member as well as the author and book name,
     * and year.
     * This an overload method for rating books when there is a member of the
     * same name
     * @param accountNum = the account number of the member who is rating (int)
     * @param author = name of the author of the book (string)
     * @param title = title of the book (string)
     * @param year = year that the book was written (int)
     * @return 0 if the rating was successful and -1 if the book or member
     * do not exist
     */
    int rateBook(int accountNum, std::string author, std::string title, int
    year);

private:

    int idCounter; // keeps track of what the used ids are (increments)
// I am not sure how I will store the book class yet.
// I don't think I can use a 2D array because some cells will have strings
// and some will have ints
};


#endif //PROJECT2_RECOMMENDATIONS_BOOK_H
