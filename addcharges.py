from datetime import datetime
import re
import argparse

lines = []

f2 = open("charges_me21_5pct.txt", "r")
content_f2 = f2.readlines()

with open("addcharges.txt", "r") as f1:
    for linenum, line in enumerate(f1):
        lines += [line.replace('         ','      '+content_f2[linenum].replace('\n','')+'              ')]

qout = open("addedchartes.txt", 'w')

for linnum, lin in enumerate(lines):
    qout.write(lines[linnum])
