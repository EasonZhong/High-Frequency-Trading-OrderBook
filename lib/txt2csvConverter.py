import csv
import sys

txt_file = r"_LogBook.txt"
csv_file = r"_LogBook.csv"

in_txt = csv.reader(open(txt_file, "rb"), delimiter = '\t')
out_csv = csv.writer(open(csv_file, 'wb'))

out_csv.writerows(in_txt)

###############

txt_file = r"_InventoryBook.txt"
csv_file = r"_InventoryBook.csv"

in_txt = csv.reader(open(txt_file, "rb"), delimiter = '\t')
out_csv = csv.writer(open(csv_file, 'wb'))

out_csv.writerows(in_txt)