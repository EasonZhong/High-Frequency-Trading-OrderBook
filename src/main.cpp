//
//  main.cpp
//  WTLCapitalInterview
//
//  Created by Sumanta Bose on 22/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "messageHandler.hpp"
#include "inventoryManager.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    WTLinventory inventory; inventory.totalProfit = 0;
    
    messageData inMsg; // inMsg is the messageData object encapsulating one row of message data.
    std::ifstream messageStream("_MessageBook.txt");
    std::ofstream orderBook("_OrderBook.txt",ios::out);
    std::ofstream logBook("_LogBook.txt",ios::out);
    logBook << "Message no.\tMessage Line\tOrderBook before transaction\tOrderBook after transaction\tProfit from transaction\tRemark\n";
    
    int messageRow = 1, cellID, value = 0; long int profit;
    std::string messageLine, messageCell, orderDetails;
    
    // Message stream starts to get read here
    while(std::getline(messageStream,messageLine)) // Loop until last line of message stream
    {
        std::stringstream lineStream(messageLine); // Read each message line
        cout << "Message row no." << messageRow << ":\n" << messageLine << endl; // For test purposes
        //logBook << "Msg #" << messageRow << "\t" << messageLine << "\t"; // Old code. Error: Prints CR
        messagePrinter(logBook, messageLine, messageRow); //New code
        
        bool decision = true; value = 0;
        cellID = 0; // cellID: 0(action), 1(orderid), 2(side), 3(quantity) and 4(price)
        while(std::getline(lineStream,messageCell,',') && cellID < 6) // Loop & QC until last cell of message line
        {
            switch (cellID)
            {
                case 0:
                    if (!actionQCcheck(messageCell[0]))
                    {
                        cout << "Invalid Action." << endl;
                        logBook << "\t\t\tInvalid Action.";
                        decision = false;
                    }
                    else
                    {
                        inMsg.action = messageCell[0];
                        cout << "Action = " << inMsg.action << endl;
                    }
                    break;
                case 1:
                    if (!intQCcheck(messageCell))
                    {
                        cout << "Invalid Order ID." << endl;
                        if (!decision)
                        {
                            logBook << " Invalid Order ID.";
                        }
                        else
                        {
                            logBook << "\t\t\tInvalid Order ID.";
                        }
                        decision = false;
                    }
                    else if (inventory.duplicateOIDcheck(mySTOLL(messageCell),inMsg.action))
                    {
                        cout << "Duplicate Order ID." << endl;
                        if (!decision)
                        {
                            logBook << " Duplicate Order ID.";
                        }
                        else
                        {
                            logBook << "\t\t\tDuplicate Order ID.";
                        }
                        decision = false;
                    }
                    else
                    {
                        inMsg.orderid = mySTOLL(messageCell);
                        cout << "Order ID = " << inMsg.orderid << endl;
                    }
                    break;
                case 2:
                    if (!sideQCcheck(messageCell[0]))
                    {
                        cout << "Invalid Side." << endl;
                        if (!decision)
                        {
                            logBook << " Invalid Side.";
                        }
                        else
                        {
                            logBook << "\t\t\tInvalid Side.";
                        }
                        decision = false;
                    }
                    else
                    {
                        inMsg.side = messageCell[0];
                        cout << "Side = " << inMsg.side << endl;
                    }
                    break;
                case 3:
                    if (!intQCcheck(messageCell))
                    {
                        cout << "Invalid Quantity." << endl;
                        if (!decision)
                        {
                            logBook << " Invalid Quantity.";
                        }
                        else
                        {
                            logBook << "\t\t\tInvalid Quantity.";
                        }
                        decision = false;
                    }
                    else
                    {
                        inMsg.quantity = mySTOL(messageCell);
                        cout << "Quantity = " << inMsg.quantity << endl;
                    }
                    break;
                case 4:
                    carriageReturnCorrector(messageCell); // To get rid of the carriage return at the end
                    if (!intQCcheck(messageCell))
                    {
                        cout << "Invalid Price." << endl;
                        if (!decision)
                        {
                            logBook << " Invalid Price.";
                        }
                        else
                        {
                            logBook << "\t\t\tInvalid Price.";
                        }
                        decision = false;
                    }
                    else
                    {
                        inMsg.price = mySTOL(messageCell);
                        cout << "Price = " << inMsg.price << endl;
                    }
                    break;
                default:
                    cout << "Invalid message length." << endl;
                    if (!decision)
                    {
                        logBook << " Invalid message length.";
                    }
                    else
                    {
                        logBook << "\t\t\tInvalid message length.";
                    }
                    decision = false;
                    break;
            }
            cellID ++ ; // Increment cellID to read the next message cell
        }
        // One row of message is read at this point
        
        if(!decision) // Quality Control check point.
        {
            cout << "Message QC check failed at row " << messageRow << ". Message ignored." << endl;
            logBook << " Message ignored." << endl;
            
        }
        else // Message QC check passed. Inventory will be updated now.
        {
            cout << "Message QC check passed." << endl;
            switch (inMsg.side)
            {
                case 'S':
                    switch (inMsg.action)
                {
                    case 'A':
                        inventory.sellInventoryAdd(inMsg); break;
                    case 'X':
                        if (!inventory.sellInventoryDelete(inMsg))
                        {
                            cout << "Delete Error: Order ID or Side or Quantity or Price mismatch." << endl;
                            logBook << "\t\t\tDelete Error: Order ID or Side or Quantity or Price mismatch.\n";
                            value = 1;
                        }
                        break;
                    case 'M':
                        if (!inventory.sellInventoryModify(inMsg))
                        {
                            cout << "Modify Error: Order ID or Side mismatch." << endl;
                            logBook << "\t\t\tModify Error: Order ID or Side mismatch.\n";
                            value = 1;
                        }
                        break;
                    default:
                        cout << "inMsg.action switch error.\n"; break;
                }
                    break;
                case 'B':
                    switch (inMsg.action)
                {
                    case 'A':
                        inventory.buyInventoryAdd(inMsg); break;
                    case 'X':
                        if (!inventory.buyInventoryDelete(inMsg))
                        {
                            cout << "Delete Error: Order ID or Side or Quantity or Price mismatch." << endl;
                            logBook << "\t\t\tDelete Error: Order ID or Side or Quantity or Price mismatch.\n";
                            value = 1;
                        }
                        break;
                    case 'M':
                        if (!inventory.buyInventoryModify(inMsg))
                        {
                            cout << "Modify Error: Order ID or Side mismatch." << endl;
                            logBook << "\t\t\tModify Error: Order ID or Side mismatch.\n";
                            value = 1;
                        }
                        break;
                    default:
                        cout << "inMsg.action switch error.\n"; break;
                }
                    break;
                default:
                    cout << "inMsg.side switch error.\n"; break;
            }
            
            // For the sake of record, we will record the OrderBook before transaction.
            orderDetails = inventory.orderBookExtractor();
            if (!value)
                logBook << orderDetails << "\t";
            
            // Initial inventory is updated at this point. Inventory transaction will take place now.
            profit = inventory.inventoryTransaction();
            
            // Inventory transaction is complete at this point. OrderBook will be updated now.
            orderDetails = inventory.orderBookExtractor();
            orderBook << orderDetails << endl;
            if (!value)
                logBook << orderDetails << "\t Transaction Profit = " << profit << "\tOkay done." << endl;
        }
        // Next message line will be read from the stream and the cycle repeated.
        messageRow++; // Increment message row number.
        cout << endl;
    }
    
    inventory.sellInventoryPrintList(); inventory.buyInventoryPrintList();
    
    messageStream.close();
    orderBook.close();
    
    logBook << "\t\t\t\tTOTAL PROFIT = " << inventory.totalProfit << endl;
    logBook.close();
    
    cout << "TOTAL PROFIT = " << inventory.totalProfit << endl;
    
    return 0;
}