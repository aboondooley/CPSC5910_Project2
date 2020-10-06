//
// Created by Alie on 9/24/2020.
//

#ifndef PROJECT2_RECOMMENDATIONS_MEMBER_H
#define PROJECT2_RECOMMENDATIONS_MEMBER_H
#include <string>
#include <utility>
#include <set>

/**
 * Member Class holds a list of members in the book rating program
 * Members are uniquely identified by their account number which is returned
 * when the account is made.
 * A list of all members and their account numbers can also be printed out
 * The list of members will automatically resize itself if necessary
 */

class Member {
public:

    /**
     * Constructor - no arg
     */
    Member();

    /**
     * Copy ctor
     * @param other Member to copy
     */
    Member(const Member &other);

    /**
     * Dtor
     */
     ~Member();

     /**
      * Assignment operator overload
      * @param another Member object to copy
      * @return me, new and improved
      */
      Member &operator=(const Member &rhs);

    /**
     * Add a new member to the "member list" by giving their name
     * @param name = name of the new member to add (string)
     * @return returns the member account number and associated member name
     * that were just added
     */
    int addNewMember(std::string name);

    /**
     * Finds the name of the member when given the Member Id
     * @param memberId member ID number
     * @return string name of Member
     */
     std::string findName(int memberId) const;


    /**
     *  Another way for members to login, this time using their account number.
     * @param memberId the account number/member id
     * @return true if the log in was successful, false if no member exists
     */
    bool login(int memberId);

    /**
     * Members can logout using their name.
     * @param memberId the member Id of the
     * @return true if the logout was successful, false if not logged in or
     * no member exists
     */
    bool logout(int memberId);

    /**
     * Print out a single account (single member)
     * @param memberId of the member to print
     */
     void printAccount(int memberId) const;

     /**
      * Prints out all of the members!
      */
      void printAllMembers();

      /**
       * Gives the number of members
       * @return number of members (successfully added members)
       */
       int size() const;

    /**
     * Allows the user to quit out of the program by ending the program.
     */
    void quit();

private:
    static const int I_CAPACITY = 30;
    struct MemberInfo {
        int accountNo;
        std::string name;
        bool loggedIn;
    };

    MemberInfo *memberArray;
    int count;
    int capacity;

    /**
     * Resizes the memberArray if the initial capacity is exceeded.
     * Happens automatically
     */
     void resize();

};


#endif //PROJECT2_RECOMMENDATIONS_MEMBER_H
