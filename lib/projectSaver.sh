#!/bin/bash 

prev=1
while [ $prev -eq 1 ];
do
	echo -e "\n Would you like to save the current set of "
	read -e -p " (MessageBook, OrderBook, LogBook & InventoryBook) as a project? Choose [y/n]: " save
	if [[ "$save" == "y" || "$save" == "Y" ]]; then
		echo -e "\n Ok. Saving project..."
		cd results/
		counter=1
		while [ -d project$counter ];
		do
			let counter=counter+1
		done
		mkdir project$counter
		cp ../_MessageBook.txt project$counter/
		cp ../_OrderBook.txt project$counter/
		cp ../_LogBook.csv project$counter/
		cp ../_InventoryBook.csv project$counter/
		echo -e " The project is saved in directory results/project$counter.\n"
		cd ..
		prev=0
	elif [[ "$save" == "n" || "$save" == "N" ]]; then
		echo -e "Ok. Project not saved...\n"
		prev=0
	else
		echo Invalid choice. Enter again
	fi
done