#!/bin/bash

./WTLCapitalInterview

cp lib/txt2csvConverter.py ./
python txt2csvConverter.py
rm txt2csvConverter.py
rm _InventoryBook.txt
rm _LogBook.txt