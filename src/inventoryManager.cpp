//
//  inventoryManager.cpp
//  WTLCapitalInterview
//
//  Created by Sumanta Bose on 22/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#include "inventoryManager.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

WTLinventory::WTLinventory() // Defining the default constructor
{
    sellHead = NULL;
    sellCurr = NULL;
    sellTemp = NULL;
    sellTail = NULL;
    
    buyHead = NULL;
    buyCurr = NULL;
    buyTemp = NULL;
    buyTail = NULL;
}

//////////////////////////////////////////////////////////////////////////////

void WTLinventory::sellInventoryAdd(const messageData& sampleMessage)
{
    sellPtr node = new sellInventory;
    node->orderid = sampleMessage.orderid;
    node->price = sampleMessage.price;
    node->quantity = sampleMessage.quantity;
    
    if (sellHead == NULL) // No existing nodes yet
    {
        sellHead = node;
        sellHead->prev = NULL;
        
        sellTail = sellHead;
        sellTail->next = NULL;
        
    }
    else if (sellHead == sellTail) // Only 1 node existing
    {
        if (node->price < sellTail->price) // Add new node to right side
        {
            sellTail->next = node;
            node->prev = sellTail;
            
            sellTail = node;
            sellTail->next = NULL;
        }
        else // Add new node to left side (either higher-price or same-price-latter-time
        {
            sellHead->prev = node;
            node->next = sellHead;
            
            sellHead = node;
            sellHead->prev = NULL;
        }
    }
    else // More than 1 node existing
    {
        if (node->price < sellTail->price) // Add new node to right of Tail
        {
            sellTail->next = node;
            node->prev = sellTail;
            
            sellTail = node;
            sellTail->next = NULL;
        }
        else if (node->price >= sellHead->price) // Add new node to the left of Head
        {
            sellHead->prev = node;
            node->next = sellHead;
            
            sellHead = node;
            sellHead->prev = NULL;
        }
        else // Insert new node to the left of current node
        {
            sellCurr = sellHead;
            while (node->price < sellCurr->price)
            {
                sellCurr = sellCurr->next;
            }
            sellTemp = sellCurr->prev;
            
            sellTemp->next = node;
            node->next = sellCurr;
            
            sellCurr->prev = node;
            node->prev = sellTemp;
        }
    }
    cout << "Successfully added sell order to inventory." << endl;
}


bool WTLinventory::sellInventoryDelete(const messageData& sampleMessage)
{
    bool status;
    sellCurr = sellHead;
    while (sellCurr!= NULL && sellCurr->orderid != sampleMessage.orderid)
    {
        sellCurr = sellCurr->next;
    }
    if (sellCurr == NULL)
    {
        cout << "Sell Node with OID = " << sampleMessage.orderid << " was not found for deletion." << endl;
        status = false;
    }
    else if(sellCurr->price != sampleMessage.price)
    {
        cout << "Sell Node with OID = " << sampleMessage.orderid << " was found, but 'prices' did not match, therefore no deletion was done." << endl;
        status = false;
    }
    else if (sellCurr->quantity != sampleMessage.quantity)
    {
        cout << "Sell Node with OID = " << sampleMessage.orderid << " was found, but 'quantities' did not match, therefore no deletion was done." << endl;
        status = false;
    }
    else
    {
        sellPtr delPtr = NULL;
        if (sellCurr == sellHead && sellCurr == sellTail) // Delete when Head and Tail are same
        {
            delPtr = sellCurr;
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
            sellHead = NULL;
            sellTail = NULL;
            sellCurr = NULL;
            sellTemp = NULL;
        }
        else if (sellCurr == sellHead && sellCurr != sellTail) // Head is to be deleted
        {
            delPtr = sellHead;
            sellHead = sellHead->next;
            sellHead->prev = NULL;
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
        }
        else if (sellCurr == sellTail && sellCurr != sellHead) // Tail is to be delted
        {
            delPtr = sellTail;
            sellTail = sellTail->prev;
            sellTail->next = NULL;
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
        }
        else // Some middle node is to be deleted
        {
            delPtr = sellCurr;
            
            sellTemp = sellCurr->prev;
            sellTemp->next = sellCurr->next;
            
            sellTemp = sellCurr->next;
            sellTemp->prev = sellCurr->prev;
            
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
        }
        cout << "Successfully deleted sell order from inventory." << endl;
        status = true;
    }
    return status;
}


bool WTLinventory::sellInventoryModify(const messageData& sampleMessage)
{
    bool status;
    sellCurr = sellHead;
    while (sellCurr!= NULL && sellCurr->orderid != sampleMessage.orderid)
    {
        sellCurr = sellCurr->next;
    }
    if (sellCurr == NULL)
    {
        cout << "Sell Node with OID = " << sampleMessage.orderid << " was not found for modification." << endl;
        status = false;
    }
    else
    {
        sellCurr->price = sampleMessage.price;
        sellCurr->quantity = sampleMessage.quantity;
        cout << "Successfully modified sell order from inventory." << endl;
        status = true;
    }
    return status;
}

//////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////

void WTLinventory::buyInventoryAdd(const messageData& sampleMessage)
{
    buyPtr node = new buyInventory;
    node->orderid = sampleMessage.orderid;
    node->price = sampleMessage.price;
    node->quantity = sampleMessage.quantity;
    
    if (buyHead == NULL) // No existing nodes yet
    {
        buyHead = node;
        buyHead->prev = NULL;
        
        buyTail = buyHead;
        buyTail->next = NULL;
        
    }
    else if (buyHead == buyTail) // Only 1 node existing
    {
        if (node->price > buyTail->price) // Add new node to right side
        {
            buyTail->next = node;
            node->prev = buyTail;
            
            buyTail = node;
            buyTail->next = NULL;
        }
        else // Add new node to left side (either lower-price or same-price-latter-time
        {
            buyHead->prev = node;
            node->next = buyHead;
            
            buyHead = node;
            buyHead->prev = NULL;
        }
    }
    else // More than 1 node existing
    {
        if (node->price > buyTail->price) // Add new node to right of Tail
        {
            buyTail->next = node;
            node->prev = buyTail;
            
            buyTail = node;
            buyTail->next = NULL;
        }
        else if (node->price <= buyHead->price) // Add new node to the left of Head
        {
            buyHead->prev = node;
            node->next = buyHead;
            
            buyHead = node;
            buyHead->prev = NULL;
        }
        else // Insert new node to the left of current node
        {
            buyCurr = buyHead;
            while (node->price > buyCurr->price)
            {
                buyCurr = buyCurr->next;
            }
            buyTemp = buyCurr->prev;
            
            buyTemp->next = node;
            node->next = buyCurr;
            
            buyCurr->prev = node;
            node->prev = buyTemp;
        }
    }
    cout << "Successfully added buy order to inventory." << endl;
}


bool WTLinventory::buyInventoryDelete(const messageData& sampleMessage)
{
    bool status;
    buyCurr = buyHead;
    while (buyCurr!= NULL && buyCurr->orderid != sampleMessage.orderid)
    {
        buyCurr = buyCurr->next;
    }
    if (buyCurr == NULL)
    {
        cout << "Buy Node with OID = " << sampleMessage.orderid << " was not found for deletion." << endl;
        status = false;
    }
    else if(buyCurr->price != sampleMessage.price)
    {
        cout << "Buy Node with OID = " << sampleMessage.orderid << " was found, but 'prices' did not match, therefore no deletion was done." << endl;
        status = false;
    }
    else if (buyCurr->quantity != sampleMessage.quantity)
    {
        cout << "Sell Node with OID = " << sampleMessage.orderid << " was found, but 'quantities' did not match, therefore no deletion was done." << endl;
        status = false;
    }
    else
    {
        buyPtr delPtr = NULL;
        if (buyCurr == buyHead && buyCurr == buyTail) // Delete when Head and Tail are same
        {
            delPtr = buyCurr;
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
            buyHead = NULL;
            buyTail= NULL;
            buyCurr = NULL;
            buyTemp = NULL;
        }
        if (buyCurr == buyHead && buyCurr != buyTail) // Head is to be deleted
        {
            delPtr = buyHead;
            buyHead = buyHead->next;
            buyHead->prev = NULL;
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
        }
        else if (buyCurr == buyTail && buyCurr != buyHead) // Tail is to be delted
        {
            delPtr = buyTail;
            buyTail = buyTail->prev;
            buyTail->next = NULL;
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
        }
        else // Some middle node is to be deleted
        {
            delPtr = buyCurr;
            
            buyTemp = buyCurr->prev;
            buyTemp->next = buyCurr->next;
            
            buyTemp = buyCurr->next;
            buyTemp->prev = buyCurr->prev;
            
            delPtr->next = NULL; delPtr->prev = NULL; delete delPtr;
        }
        cout << "Successfully deleted buy order from inventory." << endl;
        status = true;
    }
    return status;
}


bool WTLinventory::buyInventoryModify(const messageData& sampleMessage)
{
    bool status;
    buyCurr = buyHead;
    while (buyCurr!= NULL && buyCurr->orderid != sampleMessage.orderid)
    {
        buyCurr = buyCurr->next;
    }
    if (buyCurr == NULL)
    {
        cout << "Buy Node with OID = " << sampleMessage.orderid << " was not found for modification." << endl;
        status = false;
    }
    else
    {
        buyCurr->price = sampleMessage.price;
        buyCurr->quantity = sampleMessage.quantity;
        cout << "Successfully modified buy order from inventory." << endl;
        status = true;
    }
    return status;
}

//////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////

void WTLinventory::sellInventoryPrintList()
{
    ofstream inventoryBook("_InventoryBook.txt",ios::out);
    inventoryBook << "Final inventory of un-bought sell orders at end of all transactions:\n(Lowest sell price first)\n" << endl;
    sellCurr = sellTail;
    int i = 1;
    while (sellCurr!=NULL)
    {
        inventoryBook << "Sell Order " << i << "\tOrderID = " << sellCurr->orderid << "\tQuantity = " << sellCurr->quantity << "\tPrice = " << sellCurr->price << endl;
        i++;
        sellCurr = sellCurr->prev;
    }
    inventoryBook.close();
}

void WTLinventory::buyInventoryPrintList()
{
    ofstream inventoryBook("_InventoryBook.txt",ios::app);
    inventoryBook << "\n\n\nFinal inventory of un-sold buy orders at end of all transactions:\n(Highest buy price first)\n" << endl;
    buyCurr = buyTail;
    int i = 1;
    while (buyCurr!=NULL)
    {
        inventoryBook << "Buy Node " << i << "\tOrderID = " << buyCurr->orderid << "\tQuantity = " << buyCurr->quantity << "\tPrice = " << buyCurr->price << endl;
        i++;
        buyCurr = buyCurr->prev;
    }
    inventoryBook.close();
}

//////////////////////////////////////////////////////////////////////////////