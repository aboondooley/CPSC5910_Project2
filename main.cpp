#include <iostream>
#include <fstream>
#include <sstream>
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


int main() {
    string filename;
    cout << "Enter rating file: ";
    cin >> filename;
    cout << endl;

    const int SIZE = 100;
    string *members = new string[SIZE]; // 1D array
    int **ratings = new int*[SIZE]; // 2D array
    for (int i = 0; i < SIZE; i++)
        ratings[i] = new int[SIZE];

    int m_count = 0, r_count = 0, r = 0, line_count = 0;
    string name, line;
    ifstream inFile;
    inFile.open(filename);

    if (inFile){
        while (getline(inFile, line) && m_count < SIZE){
            if (line_count % 2 == 0){ // even lines are members
                members[m_count++] = line;
            } else { // odd lines are ratings
                r_count = 0;
                istringstream iss (line);
                while (iss >> r){
                    ratings[m_count-1][r_count++] = r;
                }
            }
            line_count++;
        }

    } else {
        cout << "ERROR: cannot open file.\n";
    }

    // number of books and members:
    cout << "# of books: " << r_count << endl;
    cout << "# of members: " << m_count << endl;
    cout << endl;

    // print out members and their ratings
    for (int i = 0; i < m_count; i++){
        cout << members[i] << endl;
        for (int j = 0; j < r_count; j++){
            cout << ratings[i][j] << " ";
        }
        cout << endl;
    }

    //deallocate
    delete[] members;
    for (int i = 0; i < SIZE; i++)
        delete[] ratings[i];
    delete[] ratings;

    return 0;
}