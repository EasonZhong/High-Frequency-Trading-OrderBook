//
//  messageHandler.hpp
//  WTLCapitalInterview
//
//  Created by Sumanta Bose on 22/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#ifndef messageHandler_hpp
#define messageHandler_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

struct messageData // Defining one row of message data
{
    char action; // Action=A (add) or X (delete) or M (modify)
    long long int orderid; // 64 bit order ID
    char side;  // Side = B (buy) or S (sell)
    long int quantity; // Order quantity
    long int price; // Order price
};

void messagePrinter(std::ofstream&, const std::string&, const int&);
void carriageReturnCorrector(std::string&);

bool intQCcheck(const std::string&);
bool actionQCcheck(const char&);
bool sideQCcheck(const char&);

void myStringToLong(const std::string&, long int&);
void myStringToLongLong(const std::string&, long int&);


long int mySTOL(const std::string&);
long long int mySTOLL(const std::string&);


#endif /* messageHandler_hpp */
