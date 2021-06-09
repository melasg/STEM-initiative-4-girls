#!/usr/bin/python
# script to convert the .txt file to code for the program
import re
data_path = 'script.txt'
blocks = []
try:
    data_file = open(data_path)
    for line in data_file:
        if line.strip() == '':
            continue
# insert string
        name = line.strip()
# line 1 and 2 for the 2x16 LCD
        line1 = data_file.readline()[:-1]
        line2 = data_file.readline()[:-1]
        if line1[0] == '<':
            line1 = chr(0x7F) + line1[1:] #set directional buttons
        if line2[0] == '>':
            line2 = chr(0x7E) + line2[1:] # set directional buttons

        line1 = line1.ljust(16)
        line2 = line2.ljust(16)

        opt1, opt2 = [x.strip() for x in data_file.readline().split(',')]
        if opt1 == 'BAD':
            break
        if opt2 == 'BAD':
            break
        blocks.append({
            'name': name,
            'line1': line1,
            'line2': line2,
            'option_1': option_1,
            'option_2': option_2
        })
finally:
    data_file.close()

try:
    output = open('data_out.txt', 'w')

    for block in blocks:
        output.write('"{0[name]}":\n'.format(block))
        output.write('.DB"{0[line1]}"\n'.format(block))
        output.write('.DB"{0[line2]}"\n'.format(block))
        output.write('.DW"{0[option_1]}" << 1\n'.format(block))
        output.write('.DW"{0[option_2]}" << 1\n'.format(block))
        output.write('\n')
finally:
    output.close()