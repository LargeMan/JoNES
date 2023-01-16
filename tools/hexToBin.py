import sys
import binascii

# Input is arg1, output is arg2
if len(sys.argv) <= 2:
    exit()

temp = []

with open(sys.argv[1], 'r') as input:
    for line in input: # should be just one
        temp += line.split()
        print(temp)

hexstring = ''.join(temp)

with open(sys.argv[2], "wb") as output:
    output.write(binascii.unhexlify(hexstring))