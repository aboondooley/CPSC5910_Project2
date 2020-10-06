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
     * @param bookId bookId of the book to rate
     * @param rating value of rating
     * @return true if the rating was successful, false if the member or
     * book doesn't exist
     */
    bool addRating(int memberId, int bookId, int rating);


    /**
     * Gets the rating for the member and book
     * @param memberId member account number
     * @param bookId the bookId of the rating to look up
     * @return the rating of the book in question
     */
     int getRating(int memberId) const;

     /**
      * Get all of the ratings for a particular member
      * @param memberId account number of the member to print for
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
    * @param bookId the bookId of the book to add
    */
    void addBook(int bookId);


private:
    const static int INITIAL_CAPACITY = 30;
    const static int RATE_ZERO = 0;
    int **ratingArray;
    int memberCapacity;
    int bookCapacity;

    void resizeCols(int newCapac);
    void resizeRows(int newCapac);
    void clear();
};


#endif //PROJECT2_RECOMMENDATIONS_RATING_H
