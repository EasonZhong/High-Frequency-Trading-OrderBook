# High-Frequency-Trading-OrderBook
#### Developed by Sumanta Bose  
##### ([sumanta001@e.ntu.edu.sg](mailto:sumanta001@e.ntu.edu.sg))
------
#### Problem Statement
Given a sequence of messages, construct an in-memory representation of the current state of the order book. An example MessageBook is of the form:

A,100600,S,1,1081

A,100601,B,9,1006
A,100602,B,30,981
A,100603,S,10,1056
A,100604,B,10,950
A,100605,S,2,1031
A,100606,B,1,1006
X,100604,B,10,950
A,100607,S,5,1031

with messages in the format **action, orderID, side, quantity, price** (e.g., A,123,B,9,1006), where

- action = A (add), X (remove), M (modify)
- orderID = unique 64 bit unsigned long long to identify each order used to reference existing orders for remove/modify
- side = B (buy), S (sell)
- quantity = positive integer indicating maximum quantity to buy/sell
- price = integer indicating max price at which to buy/min price to sell

After every message, write the state of order book (best sell price and best buy price) in this format:
[price,S,order qty of first sell order, order qty of second sell order, ..]
[price,B,order qty of first buy order, order qty of second buy order, ..]

For example, the previous example above would yield the output below:
[1081,S,1][NAN]
[1081,S,1][1006,B,9]
[1081,S,1][1006,B,9]
[1056,S,10][1006,B,9]
[1056,S,10][1006,B,9]
[1031,S,2][1006,B,9]
[1031,S,2][1006,B,9,1]
[1031,S,2][1006,B,9,1]
[1031,S,2,5][1006,B,9,1]
[1031,S,5][1006,B,9,1]
[1031,S,4][1006,B,9,1]

------
#### Solution

Please see the file **ReadMe.pdf** for a detailed documentation on the algorithmic solution approach, C++ implementation, framework and depdencies. It also explains the process with an illustration and also exception handling. The runtime environment and user interface is also discussed in detail

------
#### How to use this Git?
Unzip the downloaded Git and run the following command in the terminal

```sh
$ bash run.sh
```
Note: g++ is necessary for compiling the C++ source code.