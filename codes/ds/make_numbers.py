import random
import sys
import struct

MAX_INT = 2100000000
MAX = 10000000

def write_numbers(filename):
    f = open(filename, 'wb')

    for i in xrange(MAX):
        num = random.randint(1, MAX_INT)
        b_num = struct.pack('i', num)
        f.write(b_num)

    f.close()

def write_numbers_str(filename):
    f = open(filename, 'w')
    for i in xrange(MAX):
        num = random.randint(1, sys.maxint)
        f.write(str(num))
        f.write('\n')

def read_numbers(filename):
    f = open(filename, 'rb')
    b_num = f.read(4)
    ret = struct.unpack('i', b_num)
    num = ret[0]
    print 'read num', num
    f.close()

filename = 'numbers.txt'
write_numbers(filename)
#read_numbers(filename)

