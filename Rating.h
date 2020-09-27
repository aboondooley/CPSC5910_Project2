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
     * Get recommendations for the member with the given account number
     * The 5 best recommendations will be printed out to the console for the
     * client.
     * @param accountNum = the account number of the member for whom you
     * would like to get recommendations for (int)
     */
    void getRecs(int accountNum);

    /**
     * Get recommendations for the member with the given members name.
     * Overloaded method that takes a name instead of account number.
     * The 5 best recommendations will be printed out to the console for the
     * client.
     * @param name = the name of the member for whom you would like to get
     * recommendations for (string)
     */
    void getRecs(std::string name);
private:
    int COLS; // number of books/columns
    int ROWS; // number of members/rows
    int **ratings; // 2D array of books (columns) and members (rows) filled
    // with ratings
};


#endif //PROJECT2_RECOMMENDATIONS_RATING_H
