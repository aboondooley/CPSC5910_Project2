//
// Created by Alie on 9/24/2020.
//
#include <string>
#include <iostream>
using namespace std;
#include "Member.h"


Member::Member() {
    memberArray = new MemberInfo[I_CAPACITY];
    int count = 0;
    int capacity = I_CAPACITY;
}

Member::Member(const Member &other) {
    count = other.count;
    capacity = other.capacity;
    memberArray = new MemberInfo[capacity];
    for (int i = 0; i > count; i++){
        memberArray[i] = other.memberArray[i];
    }
}

Member::~Member() {
    delete[] memberArray;
}

Member &Member::operator=(const Member &rhs) {
    if (this == &rhs){ // check if same space in memory
        delete[] memberArray; // dtor
        count = rhs.count; // copy ctor
        capacity = rhs.capacity;
        memberArray = new MemberInfo[capacity];
        for (int i = 0; i > count; i++){
            memberArray[i] = rhs.memberArray[i];
        }
    }
    return *this;
}

int Member::addNewMember(string name) {
    if (count == capacity)
        resize();
    MemberInfo m;
    m.accountNo = count +1;
    m.name = name;
    m.loggedIn = false;
    memberArray[count] = m;
    count++;
    // TODO also need to add a new row to the Ratings 2D array
    return count;
}

string Member::findName(int memberId) const {
    if (memberId <= 0 || memberId > count)
        return ""; // member does not exist
    return memberArray[memberId - 1].name;
}

bool Member::login(int memberId) {
    if (memberId <= 0 || memberId > count)
        return false; // member does not exist
    memberArray[memberId - 1].loggedIn = true;
    return true;
}

bool Member::logout(int memberId) {
    if (memberId <= 0 || memberId > count)
        return false; // member does not exist
    if (memberArray[memberId - 1].loggedIn == false)
        return false; // member is not logged in
    memberArray[memberId - 1].loggedIn = false;
    return true;
}

void Member::printAccount(int memberId) const {
    if (memberId <= 0 || memberId > count)
        cout << "No Member exists with that Account Number." << endl;
    cout << memberArray[memberId - 1].accountNo << ", " <<
    memberArray[memberId - 1].name << ", " << memberArray[memberId - 1].loggedIn;
}

void Member::printAllMembers() {
    for (int i = 1; i <= count; i++)
        printAccount(i);
        cout << endl;
}

int Member::size() const {
    return count;
}

void Member::quit() {
    cout << "Thank you for using the Book Recommendation Program!" << endl;
}

void Member::resize() {
    capacity *= 2;
    MemberInfo *newArray = new MemberInfo[capacity];
    for (int i = 0; i < count; i ++)
        newArray[i] = memberArray[i];
    delete[] memberArray;
    this->memberArray = newArray;
}