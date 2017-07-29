#!/bin/bash

cd src/

if [ -e WTLCapitalInterview ]; then
	cp WTLCapitalInterview ../
else
	if [ -e Make.log ]; then
		rm Make.log
	else
		make > Make.log 2>&1
		cp WTLCapitalInterview ../
	fi
fi

cd ..