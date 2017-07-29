//
//  messageHandler.cpp
//  WTLCapitalInterview
//
//  Created by Sumanta Bose on 22/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#include "messageHandler.hpp"
#include "inventoryManager.hpp"
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>

using namespace std;

void messagePrinter(std::ofstream& myFile, const std::string& mLine, const int& mRow)
{
    myFile << "Msg #" << mRow << "\t" ;
    
    for (int i = 0 ; mLine[i] != '\0' ; i++)
    {
        if (mLine[i] == char(13))
        {
            break;
        }
        else
        {
            myFile << mLine[i];
        }
    }
    myFile << "\t";
}

void carriageReturnCorrector(string& myString)
{
    int i = 0;
    for (i = 0 ; myString[i] != '\0' ; i++)
    {
        if (myString[i] == char(13))
        {
            myString[i] = '\0';
            break;
        }
    }
}

bool intQCcheck(const string& myString)
{
    bool decision = true;
    char c; int intc;
    for (int i = 0 ; myString[i] != '\0' ; i++)
    {
        c = myString[i];
        intc = c - '0';
        
        if ( (intc < 0 || intc > 9) && intc != -35) // intc = -35 for char(13) carriage return
        {
            decision = false;
        }
    }
    return decision;
}


bool actionQCcheck(const char& action)
{
    bool decision;
    if (action == 'A' || action == 'M' || action == 'X')
    {
        decision = true;
    }
    else
    {
        decision = false;
    }
    return decision;
}


bool sideQCcheck(const char& side)
{
    bool decision;
    if (side == 'S' || side == 'B')
    {
        decision = true;
    }
    else
    {
        decision = false;
    }
    return decision;
}


bool WTLinventory::duplicateOIDcheck(const long long int& tempOID, const char& action)
{
    bool decision = false;

    if (action == 'A')
    {
        buyCurr = buyHead;
        while (buyCurr != NULL)
        {
            if (buyCurr->orderid == tempOID)
            {
                decision = true;
                break;
            }
            buyCurr = buyCurr->next;
        }
        
        sellCurr = sellHead;
        while (sellCurr != NULL)
        {
            if (sellCurr->orderid == tempOID)
            {
                decision = true;
                break;
            }
            sellCurr = sellCurr->next;
        }
    }
    else
    {
        decision = false;
    }
    return decision;
}



long int mySTOL(const string& strVal)
{
    long int longVal = 0, intc; char c;
    for (int i = 0 ; strVal[i] != '\0' ; i++)
    {
        c = strVal[i];
        intc = c - '0';
        longVal = 10*longVal + intc;
    }
    return longVal;
}


long long int mySTOLL(const string& strVal)
{
    long long int longLongVal = 0, intc; char c;
    for (int i = 0 ; strVal[i] != '\0' ; i++)
    {
        c = strVal[i];
        intc = c - '0';
        longLongVal = 10*longLongVal + intc;
    }
    return longLongVal;
}