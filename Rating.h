//
// Created by Alie on 9/24/2020.
//

#ifndef PROJECT2_RECOMMENDATIONS_RATING_H
#define PROJECT2_RECOMMENDATIONS_RATING_H

#include <iostream>


/**
 * The Rating class holds a 2D array of the ratings for all members for all
 * books in the "library". Members can ask for recommendations from the
 * rating class, based on books that other members have rated highly who have
 * similar taste.
 *
 */
class Rating {
public:

    /**
     * Constructor - no arg
     */
    Rating();

    /**
     * Copy constructor
     * @param other Rating object to copy
     */
    Rating(const Rating &other);

    /**
     * Assignment operator
     * @param rhs Rating object to copy
     * @return myself, new and improved
     */
    Rating &operator=(const Rating &rhs);

    /**
     * Dtor
     */
    ~Rating();

    /**
     * Add a rating for a particular member for a particular book
     * @param memberId account number of the rating member
     * @param isbn the ISBN of the book to rate
     * @param rating value of rating
     * @return true if the rating was successful, false if the member or
     * book doesn't exist
     */
    bool addRating(int memberId, int isbn, int rating);


    /**
     * Gets the rating for the member and book
     * @param memberId member account number
     * @param isbn the bookId of the rating to look up
     * @return the rating of the book in question, -100 if the member or book
     * does not exist
     */
     int getRating(int memberId, int isbn) const;

     /*
     /**
      * Get all of the ratings for a particular member and print them
      * @param memberId account number of the member to print for

      void printMemberRatings(int memberId) const;
      */

    /**
     * Get recommendations for the member with the given account number
     * The books that with the closest score loved and liked will be recommended
     * @param memberId the account number of the member for whom you
     * would like to get recommendations for (int)
     * @return the account number of the member with the most similar ratings
     */
    int mostSimilar(int memberId) const;

    /**
     * Adds a member to the rating 2D array - adds a row for a new member
     * Sets all of their ratings for that member to zero
     * @param memberId the account number of the member to add
     */
    void addMember(int memberId);

    /**
    * Adds a book to the rating 2D array - adds a column for a new book
    * Sets all of their ratings for that book to zero
     * @param isbn the ISBN of the book to add
    */
    void addBook(int isbn);


private:
    const static int INITIAL_CAPACITY = 30;
    const static int RATE_ZERO = 0;
    int **ratingArray;
    int memberCount;
    int bookCount;
    int memberCapacity;
    int bookCapacity;

    /**
     * Doubles the number of columns (bookCapacity) in the ratingArray
     * Happens automatically
     */
    void resizeCols();
    /**
     * Doubles the number of rows (memberCapacity) in the ratingArray
     * Happens automatically
     */
    void resizeRows();
    /**
     * Same functionality as the dtor but can be called from other methods
     * Clears all ratings, books, and members and deallocates from The Heap
     */
    void clear();

    /**
     * Calculates a compatibility score between two members
     * @param memberId the account number of one member
     * @param otherMember the account number of the other member
     * @return the compatability score of the two members
     */
    int calcScore(int memberId, int otherMember) const;

};


#endif //PROJECT2_RECOMMENDATIONS_RATING_H
