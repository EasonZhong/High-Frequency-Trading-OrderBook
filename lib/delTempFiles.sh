#!/bin/bash

clear
echo -e "\n Hi $USER, Thanks for using Sumanta's [Sell/Buy order MessageBook -> OrderBook] program!"
echo -e " (Developed by Sumanta Bose for WTL Capital Pte. Ltd. interview) © 2017"
echo -e " [Email: sumanta001@e.ntu.edu.sg ; Phone: +65 98612535]"
echo -e "\n Before exiting the program, please make backups of any files if your have to.\n All temporary files will be deleted."
echo -e "\n\t"
read -p " Press any key to exit... "


if [ -e WTLCapitalInterview ]; then
   		rm WTLCapitalInterview
   	fi

   	if [ -e _MessageBook.txt ]; then
   		rm _MessageBook.txt
   	fi

   	if [ -e _InventoryBook.csv ]; then
   		rm _InventoryBook.csv
   	fi

   	if [ -e _OrderBook.txt ]; then
   		rm _OrderBook.txt
   	fi

   	if [ -e _LogBook.csv ]; then
   		rm _LogBook.csv
   	fi

   	cd src/
   	make clean > MakeClean.log 2>&1
   	rm MakeClean.log
   	cd ..
   	rm *.txt
   	rm *.csv