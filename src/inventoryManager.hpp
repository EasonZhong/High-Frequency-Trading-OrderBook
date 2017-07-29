//
//  inventoryManager.hpp
//  WTLCapitalInterview
//
//  Created by Sumanta Bose on 22/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#ifndef inventoryManager_hpp
#define inventoryManager_hpp

#include <stdio.h>
#include "messageHandler.hpp"

std::string myLTOS(long int);

class WTLinventory
{
private:
    
    /////// Defining Sell Inventory Node
    typedef struct sellInventory
    {
        long long int orderid; // 64 bit order ID
        long int quantity; // Order quantity
        long int price; // Order price
        sellInventory* next;
        sellInventory* prev;
    }* sellPtr; // sellPtr is the same as sellInventory* i.e. a pointer pointing to a sellInventory object
    
    sellPtr sellHead, sellCurr, sellTemp, sellTail; // Head, Current, Temporary and Tail sellPtr
    
    
    /////// Defining Buy Inventory Node
    typedef struct buyInventory
    {
        long long int orderid; // 64 bit order ID
        long int quantity; // Order quantity
        long int price; // Order price
        buyInventory* next;
        buyInventory* prev;
    }* buyPtr; // buyPtr is the same as buyInventory* i.e. a pointer pointing to a buyInventory object
    
    buyPtr buyHead, buyCurr, buyTemp, buyTail; // Head, Current, Temporary and Tail buyPtr
    
    struct orderBookLine
    {
        std::string sBlockLHS;
        std::string bBlockRHS;
    };
    
    
public:
    WTLinventory();// {} // Default constructor
    ~WTLinventory() {} // Default destructor
    
    bool duplicateOIDcheck(const long long int&, const char&);
    
    void sellInventoryAdd(const messageData&);
    bool sellInventoryDelete(const messageData&);
    bool sellInventoryModify(const messageData&);
    
    void buyInventoryAdd(const messageData&);
    bool buyInventoryDelete(const messageData&);
    bool buyInventoryModify(const messageData&);
    
    long int inventoryTransaction();
    
    void sellInventoryPrintList();
    void buyInventoryPrintList();
    
    std::string orderBookExtractor();
    
    long int totalProfit;
};

#endif /* inventoryManager_hpp */
