// Passenger.h - Data structures for the booking system
#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

// ─── Passenger info ───
struct Passenger {
    string name;
    string phone;
    string age;
    int numSeats   = 0;
    int routeIndex = -1;
};

// ─── Route info ───
struct Route {
    string from;
    string to;
    int hours;
    int price;  // per seat in PKR
};

// All Pakistan city routes
const int TOTAL_ROUTES = 8;
inline Route routes[TOTAL_ROUTES] = {
    {"Islamabad", "Lahore",        4,  2000},
    {"Islamabad", "Karachi",      18,  5000},
    {"Islamabad", "Peshawar",      2,  1500},
    {"Islamabad", "Quetta",       12,  4500},
    {"Islamabad", "Muzaffarabad",  3,  2500},
    {"Lahore",    "Karachi",      16,  4000},
    {"Lahore",    "Multan",        5,  1800},
    {"Karachi",   "Hyderabad",     2,  1000},
};

#endif
