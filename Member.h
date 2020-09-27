//
// Created by Alie on 9/24/2020.
//

#ifndef PROJECT2_RECOMMENDATIONS_MEMBER_H
#define PROJECT2_RECOMMENDATIONS_MEMBER_H
#include <string>
#include <utility>
#include <set>

/**
 * The Member class is a combo of two unordered sets of pairs of type int and
 * string. One set holds all the members in the group and the other holds all
 * the members that are currently logged in.
 * Members can add a new member, log in, and logout.
 * It also assigns account numbers to new members by incrementing the account
 * number each time.
 */

// *** Note that loading external data should be done by the main method ***

class Member {
public:
    /**
     * Add a new member to the "member list" by giving their name
     * @param name = name of the new member to add (string)
     * @return returns the member account number and associated member name
     * that were just added
     */
    std::pair<int, std::string>  addNewMember(std::string name);

    /**
     *  Members can log in using their name.
     * @param name = the name of the member to login (string)
     * @return 0 indicates success and -1 indicates an issue
     */
    int login(std::string name);

    /**
     *  Another way for members to login, this time using their account number.
     * @param accountNum = the acount number of the member to login
     * @return 0 indicates success and -1 indicates an issue
     */
    int login(int accountNum);

    /**
     * Members can logout using their name.
     * @param name = the name of the member to logout (string)
     * @return 0 indicates success, -1 indicates the member was not logged in
     */
    int logout(std::string name);

    /**
     * Members can logout, this time using their account number.
     * @param accountNum = the account number of the member to logout (int)
     * @return 0 indicates success, -1 indicates the member was not logged in
     */
    int logout(int accountNum);

    /**
     * Allows the user to quit out of the program by ending the program.
     */
    void Quit();

private:
    std::set<std::pair<int , std::string>> members; // keeps an unordered
    // list of all members (list of pairs)
    std::set<std::pair<int , std::string>> loggedIn; // keeps an unordered
    // list of members that are currently logged in (list of pairs)
    int idCounter; // keeps track of what the used ids are (increments)
    Member(); // ctor
    ~Member(); // dtor


};


#endif //PROJECT2_RECOMMENDATIONS_MEMBER_H
