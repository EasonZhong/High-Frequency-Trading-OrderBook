#!/bin/bash
#
##  run.sh
##  WTLCapitalInterview
##
##  Created by Sumanta Bose on 25/7/17.
##  Copyright © 2017 Sumanta Bose. All rights reserved.
##


[ -z $BASH ] || shopt -s expand_aliases
alias BEGINCOMMENT="if [ ]; then"
alias ENDCOMMENT="fi"

bash lib/displayMenu.sh
bash lib/compileWTLcode.sh

val=1

while [ $val -eq 1 ];
do
	bash lib/displayMenu.sh

	read -e -p "Enter your choice: " choice

	while [[ $choice = "" ]];
	do
		read -e -p "Enter your choice: " choice
	done

	if [ $choice -eq 1 ]; then

		echo -e "\n\t Choice (1): Read a quick guide about using the program.\n"
		cat doc/QuickGuide.txt
	
		back=1
		while [ $back -eq 1 ];
		do
			read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice

			while [[ $menuChoice = "" ]];
			do
				read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice
			done

			if [ $menuChoice -eq 1 ]; then
				back=2
			elif [ $menuChoice -eq 0 ]; then
				echo -e "\n\t Choice (0): Exiting the program.\n\t Ready to exit.\n"
				
				back=0
				val=0
			else
				echo Invalid choice. Enter again
			fi
		done

	elif [ $choice -eq 2 ]; then

		echo -e "\n\t Choice (2): Run the program using predefined sample MessageBooks.\n"

		cd sample/
		echo -e "List of predefined sample MessageBooks in directory /sample are:\n"
		ls _MessageBook*

		echo -e "\n"
		filechoice=0
		while [ $filechoice -eq 0 ];
		do
			read -e -p "Choose your prefered input MessageBook file (TAB completion enabled): " inputfile
			
			while [[ $inputfile = "" ]];
			do
				read -e -p "Choose your prefered input MessageBook file (TAB completion enabled): " inputfile
			done

			validfile=0
			while [ $validfile -eq 0 ];
			do
				if [[ $inputfile == *.csv ]]; then
					validfile=1
				elif [[ $inputfile == *.txt ]]; then
					validfile=1
				else
					echo -e "\nMessageBook file is neither .txt nor .csv. Other filetypes are not allowed."
					read -e -p "Choose your prefered input MessageBook file (TAB completion enabled): " inputfile
				fi
			done

			if [ -e $inputfile ]; then
					filechoice=1
			else
				echo -e "\nInvalid choice, No such file exists. Enter again."
			fi
		done

		echo -e "\n"
		read -p "You have choosen $inputfile. Program will execute now. Press any key to continue... "

		cp $inputfile ../_MessageBook.txt
		cd ..
		bash lib/invokeWTLcode.sh

		cat doc/Summary.txt
		read -p "Hi $USER, Press any key to open the OrderBook and LogBook."
		open _LogBook.csv
		open _OrderBook.txt
		
		bash lib/projectSaver.sh

		back=1
		while [ $back -eq 1 ];
		do
			read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice

			while [[ $menuChoice = "" ]];
			do
				read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice
			done

			if [ $menuChoice -eq 1 ]; then
				back=2
			elif [ $menuChoice -eq 0 ]; then
				echo -e "\n\t Choice (0): Exiting the program.\n\t Ready to exit.\n"
				
				back=0
				val=0
			else
				echo Invalid choice. Enter again
			fi
		done

	elif [ $choice -eq 3 ]; then

		echo -e "\n\t Choice (3): Run the program using newly generated random MessageBook.\n"
		echo -e "\tNOTE: GENERATED MessageBook IS REALISTIC WITH OCASSIONAL ERROR MESSAGES."

		bash lib/RandMsgGen.sh
		read -p "Hi $USER, Press any key to open the newly generated random MessageBook."
		open _MessageBook.txt
		echo -e "\n"
		read -p "Program will execute now using the newly generated random MessageBook. Press any key to continue... "

		bash lib/invokeWTLcode.sh

		cat doc/Summary.txt
		read -p "Hi $USER, Press any key to open the OrderBook and LogBook."
		open _LogBook.csv
		open _OrderBook.txt
		
		bash lib/projectSaver.sh

		back=1
		while [ $back -eq 1 ];
		do
			read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice

			while [[ $menuChoice = "" ]];
			do
				read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice
			done

			if [ $menuChoice -eq 1 ]; then
				back=2
			elif [ $menuChoice -eq 0 ]; then
				echo -e "\n\t Choice (0): Exiting the program.\n\t Ready to exit.\n"
				
				back=0
				val=0
			else
				echo Invalid choice. Enter again
			fi
		done

	elif [ $choice -eq 4 ]; then

		echo -e "\n\t Choice (4): Run the program using external user supplied MessageBook.\n"

		echo -e "List of .txt and .csv files in root directory are:\n"
		ls *.txt *.csv

		echo -e "\n"
		filechoice=0
		while [ $filechoice -eq 0 ];
		do
			read -e -p "Choose your prefered input MessageBook file (TAB completion enabled): " inputfile
			
			while [[ $inputfile = "" ]];
			do
				read -e -p "Choose your prefered input MessageBook file (TAB completion enabled): " inputfile
			done

			validfile=0
			while [ $validfile -eq 0 ];
			do
				if [[ $inputfile == *.csv ]]; then
					validfile=1
				elif [[ $inputfile == *.txt ]]; then
					validfile=1
				else
					echo -e "\nMessageBook file is neither .txt nor .csv. Other filetypes are not allowed."
					read -e -p "Choose your prefered input MessageBook file (TAB completion enabled): " inputfile
				fi
			done

			if [ -e $inputfile ]; then
					filechoice=1
			else
				echo -e "\nInvalid choice, No such file exists. Enter again."
			fi
		done

		echo -e "\n"
		read -p "You have choosen $inputfile. Program will execute now. Press any key to continue... "

		BEGINCOMMENT
		if [[ $inputfile == *.csv ]]; then
			cp $inputfile _MessageBook.txt
		else
			:
		fi
		ENDCOMMENT

		cp $inputfile _MessageBook.txt
		bash lib/invokeWTLcode.sh

		cat doc/Summary.txt
		read -p "Hi $USER, Press any key to open the OrderBook and LogBook."
		open _LogBook.csv
		open _OrderBook.txt
		
		bash lib/projectSaver.sh

		back=1
		while [ $back -eq 1 ];
		do
			read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice

			while [[ $menuChoice = "" ]];
			do
				read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice
			done

			if [ $menuChoice -eq 1 ]; then
				back=2
			elif [ $menuChoice -eq 0 ]; then
				echo -e "\n\t Choice (0): Exiting the program.\n\t Ready to exit.\n"
				
				back=0
				val=0
			else
				echo Invalid choice. Enter again
			fi
		done

	elif [ $choice -eq 5 ]; then

		echo -e "\n\t Choice (5): Read the actual prolem statement in detail."
		echo -e "\t -- TXT file defining the problem statement will open --\n"
		open doc/CodingExerciseVer2.txt

		back=1
		while [ $back -eq 1 ];
		do
			read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice

			while [[ $menuChoice = "" ]];
			do
				read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice
			done

			if [ $menuChoice -eq 1 ]; then
				back=2
			elif [ $menuChoice -eq 0 ]; then
				echo -e "\n\t Choice (0): Exiting the program.\n\t Ready to exit.\n"
				
				back=0
				val=0
			else
				echo Invalid choice. Enter again
			fi
		done

	elif [ $choice -eq 6 ]; then

		echo -e "\n\t     Choice (6): Read the detailed documentation of this program."
		echo -e "\t -- PDF file containing detailed documentation of program will open --\n"
		open ReadMe.pdf # Todo : if error cannot open

		back=1
		while [ $back -eq 1 ];
		do
			read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice

			while [[ $menuChoice = "" ]];
			do
				read -e -p "Do you wish to (1) Go back to main menu, or (0) Exit program ? : " menuChoice
			done

			if [ $menuChoice -eq 1 ]; then
				back=2
			elif [ $menuChoice -eq 0 ]; then
				echo -e "\n\t Choice (0): Exiting the program.\n\t Ready to exit.\n"
				
				back=0
				val=0
			else
				echo Invalid choice. Enter again
			fi
		done

	elif [ $choice -eq 0 ]; then
		echo -e "\n\t Choice (0): Exiting the program.\n\t Ready to exit.\n"
		
		val=0
	else
		read -p "Invalid choice. Press any key to continue... "
	fi
done

bash lib/delTempFiles.sh
clear
