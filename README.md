# High-Frequency-Trading-OrderBook
#### Developed by [Sumanta Bose](https://sumantabose.github.io)
##### ([sumanta001@e.ntu.edu.sg](mailto:sumanta001@e.ntu.edu.sg))
------
#### Problem Statement
Given a sequence of messages, construct an in-memory representation of the current state of the order book. An example MessageBook is of the form:

A,1000,S,1,120<br/>
A,1001,S,4,115<br/>
A,1002,B,3,108<br/>
A,1003,S,5,105<br/>
A,1004,S,6,105<br/>
A,1005,B,5,110<br/>
A,1006,B,2,113<br/>
A,1007,B,6,118<br/>

with messages in the format **action, orderID, side, quantity, price** (e.g., A,123,B,9,1006), where

- action = A (add), X (remove), M (modify)
- orderID = unique 64 bit unsigned long long to identify each order used to reference existing orders for remove/modify
- side = B (buy), S (sell)
- quantity = positive integer indicating maximum quantity to buy/sell
- price = integer indicating max price at which to buy/min price to sell

After every message, write the state of order book (best sell price and best buy price) in this format:
[price,S,order qty of first sell order, order qty of second sell order, ..][price,B,order qty of first buy order, order qty of second buy order, ..]

For example, the previous example above would yield the output below:

[120,S,1][NAN]<br/>
[115,S,4][NAN]<br/>
[115,S,4][108,B,3]<br/>
[105,S,2][NAN]<br/>
[105,S,2,6][NAN]<br/>
[105,S,3][NAN]<br/>
[105,S,1][NAN]<br/>
[120,S,1][118,B,1]<br/>

For further details read the problem state in detail [here](https://github.com/sumantabose/High-Frequency-Trading-OrderBook/blob/master/doc/CodingExerciseVer2.txt).

------
#### Solution

Please see the file [**ReadMe.pdf**](https://github.com/sumantabose/High-Frequency-Trading-OrderBook/blob/master/ReadMe.pdf) for a detailed documentation on the algorithmic solution approach, C++ implementation, framework and depdencies. It also explains the process with an illustration and also exception handling. The runtime environment and user interface is also discussed in detail

------
#### How to use this Git?
Unzip the downloaded Git and run the following command in the terminal

```sh
$ bash run.sh
```
Note: g++ is necessary for compiling the C++ source code.

------
#### Afterword
Thanks for using my [Sell/Buy order MessageBook → OrderBook] program.<br/>
This program was developed by Sumanta Bose for WTL Capital Pte. Ltd. interview, an algorithmic high frequency trading (HTF) firm in Singapore. Similar problem statements on OrderBook construction is given by mainstream HFT firms like Jump Trading, Flow Traders, etc.