#include <iostream>
//#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include "Book.h"
#include "Member.h"
#include "Rating.h"

using namespace std;

/*
 * Asks the user for the filepath to the books file and another for the
 * ratings and users.
 * Creates a Book object and adds each BookLog to the Book object as it reads
 * in from the file and prints out each BookLog in the Book object.
 * Create a Member object with MemberInfo struct for each member and creates
 * a Rating object to hold all the ratings.
 * Runs an interactive session where the user can add new books, ratings, and
 * members, as well as see their ratings and get recommendations.
 *
 * @return 0
 */

/**
 * Gives the basic menu that allows the user to log in, quit, and add a new
 * member or a new book.
 * @param m Member object
 * @param b Book object
 * @param r Rating object
 */
void outMenu(Member &m, Book &b, Rating &r);

/**
 * Gives the menu for a user that is signed in. They can do more things
 * rating books, view their ratings, and see recommended books.
 * @param m Member object
 * @param b Book object
 * @param r Rating object
 * @param memberId the current logged in user
 */
void inMenu(Member &m, Book &b, Rating &r, int memberId);




/**
 * Reads in a file and then adds a new book for each line
 * in the file.
 * @param filename full path of the file with books
 * @param book a book object where you will store each individual BookLog
 */
void readInBooks(string filename, Book &books, Rating &ratings) {
    int b_count = 0, bookId = 0;
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
                bookId = books.addNewBook(++b_count, author, title, year);
                ratings.addBook(bookId + 1); // need to also add a new book to
                // ratingArray
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
 * Reads in a file and then adds a new member to the members array and adds
 * their ratings to the Ratings array
 * @param filename full path of the file with ratings
 * @param rating a Rating object
 * @param member a Member object
 */
void readInRatings(string filename, Member &member, Rating &rating) {
    int m_count = 0, r_count = 0, r = 0, line_count = 0;
    string line;
    ifstream inFile;
    inFile.open(filename);

    if (inFile) {
        while (getline(inFile, line)) {
            if (line_count % 2 == 0) { // even lines are members
                m_count = member.addNewMember(line);
                rating.addMember(m_count);
            } else { // odd lines are ratings
                r_count = 0;
                istringstream iss(line);
                while (iss >> r) {
                    rating.addRating(m_count, ++r_count, r);
                }
            }
            line_count++;
        }
    } else {
        cout << "ERROR: cannot open file.\n";
    }
}

void inMenu(Member &m, Book &b, Rating &r, int memberId) {
    cout << "************** MENU **************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Rate book                   *" << endl;
    cout << "* 4. View ratings                *" << endl;
    cout << "* 5. See recommendations         *" << endl;
    cout << "* 6. Logout                      *" << endl;
    cout << "**********************************" << endl;
    cout << endl;
    cout << "Enter a menu option:" << endl;

    int choice, account, isbn, bookId, newRate, checkRate, mostSim;
    string newMem, name, author, title, year, rerate;
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Enter the name of the new member:" << endl;
            cin.ignore();
            getline(cin, newMem);
            account = m.addNewMember(newMem);
            r.addMember(account); // add to rating object as well
            name = m.findName(account);
            cout << name << " (account #: " << account << ") was added" << endl;
            inMenu(m, b, r, memberId);
            break;
        case 2:
            cout << "Enter the author of the new book:" << endl;
            cin.ignore();
            getline(cin, author);
            cout << "Enter the title of the new book:" << endl;
            cin.ignore();
            getline(cin, title);
            cout << "Enter the year (or range of years) of the new book:" <<
            endl;
            cin.ignore();
            getline(cin, year);
            isbn = b.size() + 1;
            bookId = b.addNewBook(isbn, author, title, year);
            r.addBook(isbn);
            b.printBook(bookId);
            cout << " was added." << endl;
            inMenu(m, b, r, memberId);
            break;
        case 3:
            b.printAllBooks();
            cout << endl;
            cout << "Enter the ISBN of the book you'd like to rate:";
            cin >> isbn;
            bookId = b.lookUpBookId(isbn);
            if (r.getRating(memberId, isbn) != 0) {
                cout << "Your current rating for ";
                b.printBook(bookId);
                cout << " => rating: " << r.getRating(memberId, isbn) << endl;
                cout << "Would you like to re-rate this book (y/n)?";
                cin >> rerate;
            }
            if (rerate == "y" || r.getRating(memberId, isbn)){
                cout << "Enter your rating:";
                cin >> newRate;
                r.addRating(memberId, isbn, newRate);
                cout << "Your new rating for ";
                b.printBook(bookId);
                cout << " => rating: " << r.getRating(memberId, isbn) << endl;
                cout << endl;
            }
            if (rerate == "n"){
                cout << "Your rating has stayed the same." << endl;
                cout << endl;
            }
            inMenu(m, b, r, memberId);
            break;
        case 4:
            cout << m.findName(memberId) << "'s ratings... " << endl;
            for (int i = 0; i < b.size(); i++) {
                b.printBook(i);
                cout << " => rating: " << r.getRating(memberId, i + 1) << en
            cout << endl;
            inMenu(m, b, r, memberId);
            break;
        case 5:
            mostSim = r.mostSimilar(memberId);
            cout << "You have similar taste in books as " << m.findName
            (mostSim) << "!" << endl;
            cout << endl;
            cout << "They really liked: " << endl;
            for (int i = 0; i < b.size(); i++) {
                checkRate = r.getRating(mostSim, i + 1);
                if (checkRate == 5 && r.getRating(memberId, i + 1) == 0) {
                    b.printBook(i);
                    cout << endl;
                }
            }
            cout << endl;
            cout << "Here are the books they liked: " << endl;
            for (int i = 0; i < b.size(); i++) {
                checkRate = r.getRating(mostSim, i + 1);
                if (checkRate == 3 && r.getRating(memberId, i + 1) == 0) {
                    b.printBook(i);
                    cout << endl;
                }
            }
            inMenu(m, b, r, memberId);
            break;
        case 6:
            m.logout(memberId);
            outMenu(m, b, r);
        default:
            cout << "In default." << endl;
            //cout << "Please enter a valid menu option." << endl;
            inMenu(m, b, r, memberId);

    }


}

void outMenu(Member &m, Book &b, Rating &r) {
    cout << "************** MENU **************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Login                       *" << endl;
    cout << "* 4. Quit                        *" << endl;
    cout << "**********************************" << endl;
    cout << endl;
    cout << "Enter a menu option:" << endl;

    int choice, account, isbn, bookId;
    string newMem, name, author, title, year;
    cin >> choice;
    switch (choice){
        case 1:
            cout << "Enter the name of the new member:" << endl;
            cin.ignore();
            getline(cin, newMem);
            account = m.addNewMember(newMem);
            r.addMember(account); // add to rating object as well
            name = m.findName(account);
            cout << name << " (account #: " << account << ") was added" << endl;
            outMenu(m, b, r);
            break;
        case 2:
            cout << "Enter the author of the new book:" << endl;
            cin.ignore();
            getline(cin, author);
            cout << "Enter the title of the new book:" << endl;
            cin.ignore();
            getline(cin, title);
            cout << "Enter the year (or range of years) of the new book:" <<
                 endl;
            cin.ignore();
            getline(cin, year);
            isbn = b.size() + 1;
            bookId = b.addNewBook(isbn, author, title, year);
            r.addBook(isbn);
            b.printBook(bookId);
            cout << " was added." << endl;
            outMenu(m, b, r);
            break;
        case 3:
            cout << "Enter member account:" << endl;
            cin >> account;
            m.login(account);
            name = m.findName(account);
            cout << name << ", you are logged in!" << endl;
            inMenu(m, b, r, account);
            break;
        case 4:
            m.quit();
            exit(0);
        default:
            cout << "Please enter a valid menu option." << endl;
            outMenu(m, b, r);
    }


}




/**
 * Main entry point for testing all functions in Book class.
 * @return 0
 */
int main() {

    string bookFile = "..\\books.txt";
    string ratingFile = "..\\ratings.txt";

    /*cout << "Enter book file:";
    cin >> bookFile;
    cout << "Enter rating file:";
    cin >> ratingFile;
    cout << endl; */

    Book books; // tests ctor
    Member members;
    Rating ratings;
    readInBooks(bookFile, books, ratings);
    readInRatings(ratingFile, members, ratings);


    // number of books and members:
    cout << "# of books: " << books.size() << endl;
    cout << "# of memberList: " << members.size() << endl;
    cout << endl;

    outMenu(members, books, ratings);


    return 0;
}