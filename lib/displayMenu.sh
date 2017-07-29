#!/bin/bash

clear
 
	title1="#### Hi $USER ####" 
	title2="Welcome to Sumanta's [Sell/Buy order MessageBook -> OrderBook] program!"
	title3="(Developed by Sumanta Bose for WTL Capital Pte. Ltd. interview) © 2017"
	title4="[Best viewed in fullscreen terminal window]"
	COLUMNS=$(tput cols)
	printf "\n%*s" $(((${#title1}+$COLUMNS)/2)) "$title1"
	printf "\n%*s" $(((${#title2}+$COLUMNS)/2)) "$title2"
	printf "\n%*s" $(((${#title3}+$COLUMNS)/2)) "$title3"
	printf "\n%*s\n\n" $(((${#title4}+$COLUMNS)/2)) "$title4"

	cat doc/Menu.txt