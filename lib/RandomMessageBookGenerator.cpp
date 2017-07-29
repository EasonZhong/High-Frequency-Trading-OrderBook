//
//  main.cpp
//  MsgGenWTL
//
//  Created by Sumanta Bose on 23/7/17.
//  Copyright © 2017 Sumanta Bose. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <string>
#include <fstream>


using namespace std;

struct messageData // Defining one row of message data
{
    char action; // Action=A (add) or X (delete) or M (modify)
    long long int orderid; // 64 bit order ID
    char side;  // Side = B (buy) or S (sell)
    long int quantity; // Order quantity
    long int price; // Order price
    long int addFlag;
};

struct addLibrary
{
    long int addIndex, price, quantity;
    long long int orderid;
    char action, side;
    bool alive;
};


string myLTOS(long int intVal)
{
    long int c; char charVal; string strVal = "\0";
    while (intVal > 0)
    {
        c = intVal % 10;
        charVal = char(c+48);
        intVal /= 10;
        strVal = charVal + strVal;
    }
    return strVal;
}

string myLLTOS(long long int intVal)
{
    long long int c; char charVal; string strVal = "\0";
    while (intVal > 0)
    {
        c = intVal % 10;
        charVal = char(c+48);
        intVal /= 10;
        strVal = charVal + strVal;
    }
    return strVal;
}


int main(int argc, const char * argv[])
{
    std::ofstream messageBook("_MessageBook.txt",ios::out);
    
    string messageChunk;
    
    long int msgSize, addCount = 0, addPopulation = 0, tempID;
    
    bool flag;
    
    do
    {
        cout << "\nHow many messages entries do you want in the MessageBook? ";
        cin >> msgSize;
        if(cin.fail() || msgSize < 1)
        {
            cout << "Invalid input. Try again." << endl;
            flag = false;
            cin.clear();
            cin.ignore(256,'\n');
        }
        else
        {
            flag = true;
        }
    }while(!flag);
    
    ////////////////
    
    long int maxPrice = 800, minPrice = 500;
    
     do
     {
     cout << "\nFor price range, enter the max price: ";
     cin >> maxPrice;
     if(cin.fail() || maxPrice < 1)
     {
     cout << "Invalid input. Try again." << endl;
     flag = false;
     cin.clear();
     cin.ignore(256,'\n');
     }
     else
     {
     flag = true;
     }
     }while(!flag);
     
     
     do
     {
     cout << "For price range, enter the min price: ";
     cin >> minPrice;
     if(cin.fail() || maxPrice < 1 || minPrice >= maxPrice)
     {
     cout << "Invalid input. Try again." << endl;
     flag = false;
     cin.clear();
     cin.ignore(256,'\n');
     }
     else
     {
     flag = true;
     }
     }while(!flag);
    
    
    ////////////////
    
    long int maxOrder = 40, minOrder = 20;
    
     do
     {
     cout << "\nFor order range, enter the max order quantity: ";
     cin >> maxOrder;
     if(cin.fail() || maxPrice < 1)
     {
     cout << "Invalid input. Try again." << endl;
     flag = false;
     cin.clear();
     cin.ignore(256,'\n');
     }
     else
     {
     flag = true;
     }
     }while(!flag);
     
     
     do
     {
     cout << "For order range, enter the min order quantity: ";
     cin >> minOrder;
     if(cin.fail() || maxPrice < 1 || minPrice >= maxPrice)
     {
     cout << "Invalid input. Try again." << endl;
     flag = false;
     cin.clear();
     cin.ignore(256,'\n');
     }
     else
     {
     flag = true;
     }
     }while(!flag);
    
    ////////////////
    
    
    
    
    long int msgStrLen = myLTOS(msgSize).length();
    long int startID = pow(10,msgStrLen);
    
    int iaction, iside, modFlag;
    long int newQty, newPrc;
    
    messageData *sampMsg;
    sampMsg = new (nothrow) messageData [msgSize];
    
    addLibrary *myAddLib;
    myAddLib = new (nothrow) addLibrary [msgSize];
    
    if (sampMsg == NULL || myAddLib == NULL)
    {
        cout << "Error. Not enough data in memory.\n";
        return 0;
    }
    else
    {
        for(long int i = 0 ; i < msgSize ; i++) // Setting up initial conditions
        {
            sampMsg[i].addFlag = 0;
            myAddLib[i].alive = false;
            myAddLib[i].addIndex = 0;
        }
        
        
        
        
        /* initialize random seed: */
        srand(static_cast<unsigned int>(time(NULL)));
        
        for(long int i = 0 ; i < msgSize ; i++)
        {
            //////////////
            
            iaction = rand() % 100 + 1;
            if (iaction < 60)
            {
                sampMsg[i].action = 'A';
            }
            else if (iaction > 80)
            {
                sampMsg[i].action = 'M';
            }
            else
            {
                sampMsg[i].action = 'X';
            }
            
            
            if (i < 0.1 * msgSize)
            {
                sampMsg[i].action = 'A';
            }
            
            //////////////
            
            if (sampMsg[i].action == 'A')
            {
                sampMsg[i].orderid = startID + i + 1;
                
                //////////////
                
                iside = rand() % 2 + 1;
                switch (iside)
                {
                    case 1:
                        sampMsg[i].side = 'S';
                        break;
                    case 2:
                        sampMsg[i].side = 'B';
                        break;
                    default:
                        break;
                }
                
                //////////////
                
                sampMsg[i].quantity = rand() % (1 + maxOrder - minOrder) + minOrder;
                
                //////////////
                
                sampMsg[i].price = rand() % (1 + maxPrice - minPrice) + minPrice;
                
                //////////////
                
                addCount =  addCount + 1 ;// cout << "addCount=" <<addCount << " ";
                sampMsg[i].addFlag = addCount;
                addPopulation ++ ;
                
                ///////
                myAddLib[addCount-1].addIndex = addCount;
                myAddLib[addCount-1].action = sampMsg[i].action;
                myAddLib[addCount-1].side = sampMsg[i].side;
                myAddLib[addCount-1].orderid = sampMsg[i].orderid;
                myAddLib[addCount-1].price = sampMsg[i].price;
                myAddLib[addCount-1].quantity = sampMsg[i].quantity;
                myAddLib[addCount-1].alive = true;
                ///////
            }
            else if (sampMsg[i].action == 'M') // M
            {
                long int check = 0, modIndex;
                tempID = rand() % addPopulation + 1;
                
                for(long int k = 1 ; k <= addCount ; k++)
                {
                    if(myAddLib[k-1].alive == true)
                    {
                        check ++;
                        if (check == tempID)
                        {
                            modIndex = k;
                            break;
                        }
                    }
                }
                // cout << "tempID=" <<tempID << ", " << "modIndex=" << modIndex << " ";
                
                modFlag = rand() % 2 + 1; // To choose if modify Price or Quantity
                switch (modFlag)
                {
                    case 1: // Modify Quantity
                        sampMsg[i].price = myAddLib[modIndex-1].price; // Since price is unmodified
                        // cout << "modQ ";
                        newQty = rand() % (1 + maxOrder - minOrder) + (minOrder + 1);
                        if (newQty == myAddLib[modIndex].quantity)
                        {
                            sampMsg[i].quantity = newQty + 1;
                            myAddLib[modIndex-1].quantity = newQty + 1; //cout << "1 ";
                        }
                        else
                        {
                            sampMsg[i].quantity = newQty;
                            myAddLib[modIndex-1].quantity = newQty; //cout << "2 ";
                        }
                        
                        break;
                    case 2: // Modify Price
                        sampMsg[i].quantity = myAddLib[modIndex-1].quantity; // Since quantity is unmodified
                        //cout << "modP ";
                        newPrc = rand() % (1 + maxPrice - minPrice) + minPrice;
                        if (newPrc == myAddLib[modIndex].price)
                        {
                            sampMsg[i].price = newPrc + 1;
                            myAddLib[modIndex-1].price = newPrc + 1; //cout << "3 ";
                        }
                        else
                        {
                            sampMsg[i].price = newPrc;
                            myAddLib[modIndex-1].price = newPrc; //cout << "4 ";
                        }
                        break;
                    default:  break;
                }
                
                sampMsg[i].orderid = myAddLib[modIndex-1].orderid;
                sampMsg[i].side = myAddLib[modIndex-1].side;
            }
            else if (sampMsg[i].action == 'X') // X
            {
                long int check = 0, delIndex;
                tempID = rand() % addPopulation + 1;
                
                for(long int k = 1 ; k <= addCount ; k++)
                {
                    if(myAddLib[k-1].alive == true)
                    {
                        check ++;
                        if (check == tempID)
                        {
                            delIndex = k;
                            break;
                        }
                    }
                }
                // cout << "tempID=" <<tempID << ", " << "delIndex=" << delIndex << " ";
                
                sampMsg[i].orderid = myAddLib[delIndex-1].orderid;
                sampMsg[i].side = myAddLib[delIndex-1].side;
                sampMsg[i].quantity = myAddLib[delIndex-1].quantity;
                sampMsg[i].price = myAddLib[delIndex-1].price;
                
                myAddLib[delIndex-1].alive = false;
                addPopulation -- ;
            }
            
            
            
            
            
            
            //cout << sampMsg[i].action << " , " << sampMsg[i].orderid << " , " << sampMsg[i].side << " , " << sampMsg[i].quantity << " , " << sampMsg[i].price << " -> " << sampMsg[i].addFlag << endl;
            
            
            string tempOID = ","+myLLTOS(sampMsg[i].orderid);
            
            messageChunk = sampMsg[i].action + tempOID + "," + sampMsg[i].side + "," + myLTOS(sampMsg[i].quantity) + "," + myLTOS(sampMsg[i].price) + "\n";
            
            // cout << messageChunk;
            messageBook << messageChunk;
            
        }
        
    }
    delete [] sampMsg;
    delete [] myAddLib;
    messageBook.close();
    
    cout << "\nRandom MessageBook with user input parameters successfully generated.\n";
    
    return 0;
}