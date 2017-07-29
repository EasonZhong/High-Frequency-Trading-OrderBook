//
//  orderBookManager.cpp
//  WTLCapitalInterview
//
//  Created by Sumanta Bose on 22/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#include "inventoryManager.hpp"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <fstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

string WTLinventory::orderBookExtractor()
{
    cout << "The OrderBook is being updated now." << endl;
    orderBookLine order;
    
    if (sellHead != NULL)
    {
        order.sBlockLHS = "[" + myLTOS(sellTail->price) + ",S," + myLTOS(sellTail->quantity);
        
        sellCurr = sellTail->prev;
        while (sellCurr != NULL && sellCurr->price == sellTail->price)
        {
            order.sBlockLHS = order.sBlockLHS + "," + myLTOS(sellCurr->quantity);
            sellCurr = sellCurr->prev;
        }
        
        order.sBlockLHS = order.sBlockLHS + "]";
        
    }
    else
    {
        order.sBlockLHS = "[NAN]";
    }

    
    ////////////////////////////////////
    
    if (buyHead != NULL)
    {
        order.bBlockRHS = "[" + myLTOS(buyTail->price) + ",B," + myLTOS(buyTail->quantity);
        
        buyCurr = buyTail->prev;
        while (buyCurr != NULL && buyCurr->price == buyTail->price)
        {
            order.bBlockRHS = order.bBlockRHS + "," + myLTOS(buyCurr->quantity);
            buyCurr = buyCurr->prev;
        }
        
        order.bBlockRHS = order.bBlockRHS + "]";
    }
    else
    {
        order.bBlockRHS = "[NAN]";
    }
    
    ////////////////////////////////////
    
    string orderBookRowEntry = order.sBlockLHS + order.bBlockRHS;
    
    cout << "OrderBook Entry: " << orderBookRowEntry << endl;
    
    return orderBookRowEntry;
}

//////////////////////////////////////////////////////////////////////////////


string myLTOS(long int intVal)
{
    int c; char charVal; string strVal = "\0";
    while (intVal > 0)
    {
        c = intVal % 10;
        charVal = char(c+48);
        intVal /= 10;
        strVal = charVal + strVal;
    }
    return strVal;
}