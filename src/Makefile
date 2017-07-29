CC=g++
CCG=g++ -std=gnu++11
CCC=g++ -std=c++11

CFLAGS= -c -Wall

WTLCapitalInterview: messageHandler.o inventoryManager.o orderBookManager.o transactionManager.o main.o
	$(CC) messageHandler.o inventoryManager.o orderBookManager.o transactionManager.o main.o -o WTLCapitalInterview

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

messageHandler.o: messageHandler.cpp messageHandler.hpp inventoryManager.hpp
	$(CC) $(CFLAGS) messageHandler.cpp messageHandler.hpp inventoryManager.hpp

inventoryManager.o: inventoryManager.cpp inventoryManager.hpp
	$(CC) $(CFLAGS) inventoryManager.cpp inventoryManager.hpp

orderBookManager.o: orderBookManager.cpp inventoryManager.hpp
	$(CC) $(CFLAGS) orderBookManager.cpp inventoryManager.hpp

transactionManager.o: transactionManager.cpp inventoryManager.hpp
	$(CC) $(CFLAGS) transactionManager.cpp inventoryManager.hpp

clean:
	rm -r *.o *.gch *.log WTLCapitalInterview