#!/bin/bash

cd lib/

g++ RandomMessageBookGenerator.cpp -o RMBG > RandMsgGen.log 2>&1

./RMBG
rm RMBG

if [ -f RandMsgGen.log ]; then
   rm RandMsgGen.log
else
   :
fi

mv _MessageBook.txt ../
cd ..