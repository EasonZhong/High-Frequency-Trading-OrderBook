//
//  transactionManager.cpp
//  WTLCapitalInterview
//
//  Created by Sumanta Bose on 22/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#include "inventoryManager.hpp"
#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

long int WTLinventory::inventoryTransaction()
{
    // cout << "Bypassing transaction. " << endl;
    
    long int profit = 0;
    
    if (sellHead == NULL && buyHead == NULL)
    {
        cout << "No sell and buy orders exist, therefore no transaction will take place." << endl;
    }
    else if (sellHead == NULL && buyHead != NULL)
    {
        cout << "No sell order exists, therefore no transaction will take place." << endl;
    }
    else if (sellHead != NULL && buyHead == NULL)
    {
        cout << "No buy order exists, therefore no transaction will take place." << endl;
    }
    else // Neither sellHead nor buyHead are NULL
    {
        if (buyTail->price < sellTail->price)
        {
            cout << "Max price buy order < Min price sell order, therefore no transaction will take place." << endl;
        }
        else
        {
            cout << "The inventory transaction is taking place now." << endl;
            while (buyTail->price >= sellTail->price)
            {
                // Transaction quantity = MINIMUM of (buyTail->quantity , sellTail->quantity)
                long int transactionQty = buyTail->quantity < sellTail->quantity ? buyTail->quantity : sellTail->quantity;
                cout << "Transaction quantity = " << transactionQty << endl;

                ////// Transaction occurs here //////
                sellTail->quantity = sellTail->quantity - transactionQty;
                buyTail->quantity = buyTail->quantity - transactionQty;
                profit = profit + transactionQty * (buyTail->price - sellTail->price);
                /////// Transaction completed ////////
                
                
                ////// Sell order (node) deletion //////
                if (sellTail->quantity == 0)
                { // cout << "1 ";
                    sellPtr delPtr = sellTail;
                    if (sellTail == sellHead)
                    { // cout << "2 ";
                        delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
                        sellHead = NULL; sellTail = NULL;
                        sellCurr = NULL; sellTemp = NULL;
                        // bestSellPrice = 1;
                    }
                    else
                    { // cout << "3 ";
                        sellTail = sellTail->prev;
                        sellTail->next = NULL;
                        delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
                        // bestSellPrice = sellTail->price;
                    }
                }
                ////// Sell order (node) deleted //////
                
                
                ////// Buy order (node) deletion //////
                if (buyTail->quantity == 0)
                { // cout << "4 ";
                    buyPtr delPtr = buyTail;
                    if (buyTail == buyHead)
                    { // cout << "5 ";
                        delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
                        buyHead = NULL; buyTail= NULL;
                        buyCurr = NULL; buyTemp = NULL;
                        // bestBuyPrice = 0;
                    }
                    else
                    { // cout << "6 ";
                        buyTail = buyTail->prev;
                        buyTail->next = NULL;
                        delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
                        // bestBuyPrice = buyTail->price;
                    }
                }
                ////// Buy order (node) deleted //////
                
                if (sellHead == NULL || buyHead == NULL)
                {
                    break;
                }
                
            } // end of while loop facilitating the transaction
            
            cout << "Transaction complete. Profit = " << profit << endl;
        } // end of inner else condition enabling transaction to occur
    } // end of inner else condition enabling transaction to occur
     
    totalProfit += profit;
    return profit;
     
} // end of inventoryTransaction function

//////////////////////////////////////////////////////////////////////////////