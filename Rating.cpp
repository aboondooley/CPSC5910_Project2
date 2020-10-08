//
// Created by Alie on 9/24/2020.
//
#include <iostream>
using namespace std;
#include "Rating.h"


Rating::Rating() {
    memberCapacity = INITIAL_CAPACITY;
    bookCapacity = INITIAL_CAPACITY;
    bookCount = 0;
    memberCount = 0;
    ratingArray = new int*[INITIAL_CAPACITY];
    for (int i = 0; i <INITIAL_CAPACITY; i++)
        ratingArray[i] = new int[INITIAL_CAPACITY];
}

Rating::Rating(const Rating &other) {
    memberCapacity = other.memberCapacity;
    bookCount = other.bookCapacity;
    bookCount = other.bookCount;
    memberCount = other.memberCount;
    int **temp = new int*[memberCapacity];
    for (int i = 0; i < memberCapacity; i++)
        temp[i] = new int[bookCapacity];
    for (int i = 0; i < memberCount; i++)
        for (int j = 0; j < bookCount; i++)
            temp[i][j] = other.ratingArray[i][j];
}

Rating &Rating::operator=(const Rating &rhs) {
    if (this != &rhs)
        clear(); // same as dtor
    memberCapacity = rhs.memberCapacity;
    bookCount = rhs.bookCapacity;
    bookCount = rhs.bookCount;
    memberCount = rhs.memberCount;
    int **temp = new int*[memberCapacity];
    for (int i = 0; i < memberCapacity; i++)
        temp[i] = new int[bookCapacity];
    for (int i = 0; i < memberCount; i++)
        for (int j = 0; j < bookCount; i++)
            temp[i][j] = rhs.ratingArray[i][j];
    return *this;
}

Rating::~Rating() {
    for (int i = 0; i < memberCapacity; i++)
        delete[] ratingArray[i];
    delete ratingArray;
}

bool Rating::addRating(int memberId, int isbn, int rating) {
    if (memberId > memberCount || isbn > bookCount)
        return false;
    ratingArray[memberId - 1][isbn - 1] = rating;
    return true;
}

int Rating::getRating(int memberId, int isbn) const {
    if (memberId > memberCount || isbn > bookCount)
        return -100; // indicates there is no
    return ratingArray[memberId - 1][isbn - 1];
}

int Rating::mostSimilar(int memberId) const {
    if (memberId > memberCount)
        return -1; // member account does not exist

    memberId--; // set equal to it's actual index
    int highScore = 0, match = 0;
    for (int j = 0; j < memberCount; j++) {
        if ((calcScore(memberId, j) > highScore) && (memberId != j)) {
            highScore = calcScore(memberId, j);
            match = j;
        }
    }
    return ++match;
}


void Rating::addBook(int isbn) {
    if (bookCount > isbn)
        throw invalid_argument("addBook error: book ISBN already exists");
    if (bookCount == bookCapacity) {
        resizeCols();
    }
    bookCount++;
    for (int i = 0; i < memberCount; i++)
        ratingArray[i][isbn - 1] = 0; // set all the ratings for the new book
        // to zero
}

void Rating::addMember(int memberId) {
    if (memberCount > memberId)
        throw invalid_argument("addMember error: member account already exists");
    if (memberCount == memberCapacity) {
        resizeRows();
    }
    memberCount++;
    for (int i = 0; i < bookCount; i++)
        ratingArray[memberId - 1][i] = 0; // set all the new member's ratings
    // to zero
}

void Rating::resizeCols() {
    bookCapacity *=2;
    int **temp = new int*[memberCapacity];
    for (int i = 0; i < memberCapacity; i++) {
        temp[i] = new int[bookCapacity];
    }
    for (int n = 0; n < memberCount; n++)
        for (int j = 0; j < bookCount; j++)
            temp[n][j] = ratingArray[n][j];
    clear();
    ratingArray = temp;
}

void Rating::resizeRows() {
    memberCapacity *=2;
    int **temp = new int*[memberCapacity];
    for (int i = 0; i < memberCapacity; i++) {
        temp[i] = new int[bookCapacity];
    }
    for (int n = 0; n < memberCount; n++) {
        for (int j = 0; j < bookCount; j++) {
            temp[n][j] = ratingArray[n][j];
        }
    }
    clear();
    ratingArray = temp;

}

void Rating::clear() {
    int old = memberCapacity / 2;
    for (int i = 0; i < old; i++)
        delete[] ratingArray[i];
    delete[] ratingArray;
}

int Rating::calcScore(int memberIndex, int otherMember) const {
    if (memberIndex > memberCount || otherMember > memberCount)
        return -1; // one of the members does not exist
    int score = 0;
    for (int i = 0; i < bookCount; i++) {
        score += (ratingArray[memberIndex][i] * ratingArray[otherMember][i]);
    }
    return score;
}
