//
// Created by Alie on 9/24/2020.
//

#include "Rating.h"


Rating::Rating() {
    memberCapacity = INITIAL_CAPACITY;
    bookCapacity = INITIAL_CAPACITY;
    ratingArray = new int*[INITIAL_CAPACITY];
    for (int i = 0; i <INITIAL_CAPACITY; i++)
        ratingArray[i] = new int[INITIAL_CAPACITY];
}

Rating::Rating(const Rating &other) {

}

Rating &Rating::operator=(const Rating &rhs) {
    return <#initializer#>;
}

Rating::~Rating() {

}

bool Rating::addRating(int memberId, int bookId, int rating) {
    return false;
}

int Rating::getRating(int memberId) const {
    return 0;
}

int Rating::mostSimilar(int memberId) const {
    return 0;
}

void Rating::addMember(int memberId) {

}

void Rating::addBook(int bookId) {

}

void Rating::resizeCols(int newCapac) {

}

void Rating::resizeRows(int newCapac) {

}

void Rating::clear() {

}
