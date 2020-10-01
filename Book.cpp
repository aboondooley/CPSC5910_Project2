//
// Created by Alie on 9/24/2020.
//
#include <string>
#include <iostream>
using namespace std;
#include "Book.h"

Book::Book() {
    library = new BookLog[I_CAPACITY];
    idCounter = 0;
    capacity = I_CAPACITY;
}

Book::Book(const Book &other) {
    this->idCounter = other.idCounter;
    this->capacity = other.capacity;
    this->library = new BookLog[capacity];
    for (int i = 0; i < idCounter; i++) {
        library[i] = other.library[i];
    }
}

Book::~Book() {
    delete[] library;
}

Book &Book::operator=(const Book &rhs) {
    if (&rhs != this) { // check that not the exact same
        delete[] library; // delete old
        this->idCounter = rhs.idCounter; // same as copy ctor
        this->capacity = rhs.capacity;
        this->library = new BookLog[capacity];
        for (int i = 0; i < idCounter; i++) {
            library[i] = rhs.library[i];
        }
    }
    return *this; // return new Book
}

int Book::addNewBook(const int isbn, const string author,
                     const string title, const string year) {
    BookLog b;
    b.isbn = isbn;
    b.author = author;
    b.title = title;
    b.year = year;
    if (idCounter == capacity) this->resize(); // check to make sure there is
    // room first
    library[idCounter++] = b; // then add book at the end
    return idCounter - 1; // since we incremented already, return the prev value
}

int Book::lookUpBookId(int isbn) const {
    for (int i = 0; i < idCounter; i++){
        if (library[i].isbn == isbn){
            return i;
        }
    }
    return UH_OH;// return -1 if isbn not found
}

void Book::printBook(int bookID) const {
    cout << library[bookID].isbn << ", " << library[bookID].author << ", " <<
    library[bookID].title << ", " << library[bookID].year << endl;
}

int Book::size() const {
    return idCounter;
}

void Book::resize() {
    this->capacity += capacity; // double the capacity
    BookLog *temp = new BookLog[capacity]; // create new dynamic array
    for (int i = 0; i < idCounter; i++) {
        temp[i] = library[i]; // copy contents over to temp
    }
    delete[] library; // gotta delete so that there are no memory leaks!
    this->library = temp; // set library field to point to copy with 2X capacity
}







