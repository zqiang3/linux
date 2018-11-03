#coding: utf-8
import sys
import random
import time
from fib_num import fib
import pdb


MAX = 10000000
TEST_NUM = 10000


def create_nums(filename, n):
    """生成随机数，写到文件"""
    f = open(filename, 'w')
    for i in xrange(n):
        num = random.randint(0, MAX)
        f.write(str(num))
        f.write('\n')

    f.close()

def record_search_result(filename, result):
    f = open(filename, 'w')
    for item in result:
        v, r = item
        f.write('{},{}'.format(v, r))
        f.write('\n')

    f.close()




def load_nums(filename):
    """从文件载入数字"""
    arr = []
    f = open(filename, 'r')
    for line in f:
        arr.append(int(line))

    return arr

def load_lines(filename):
    data = []
    f = open(filename, 'r')
    for line in f:
        line = line.strip()
        values = line.split(',')
        values = map(int, values)
        data.append(values)

    return data



def find_it(arr, value):
    """普通查找算法"""
    if not isinstance(arr, list):
        return 0 

    for i in arr:
        if i == value:
            return 1 

    return 0 


def binary_search(arr, value):
    """二分查找算法"""
    return _b_search(value, arr, 0, len(arr) - 1)


def _b_search(value, arr, left, right):
    if left > right:
        return 0 

    mid = (left + right) / 2
    mid_value = arr[mid]
    if value == mid_value:
        return 1
    elif value > mid_value:
        return _b_search(value, arr, mid+1, right)
    else:
        return _b_search(value, arr, left, mid-1)


def binary_search_pro(arr, value):
    """二分查找算法"""
    return _b_search_pro(value, arr, 0, len(arr) - 1)


def _b_search_pro(value, arr, left, right):
    if left > right:
        return False

    if value < arr[left]:
        return False
    elif value > arr[right]:
        return False

    if left == right:
        mid = left
    else:
        _mid = (value - arr[left]) * 1.0 / (arr[right] - arr[left]) * (right - left)
        mid = left + int(_mid) 

    mid_value = arr[mid]
    if value == mid_value:
        return True
    elif value > mid_value:
        return _b_search_pro(value, arr, mid+1, right)
    else:
        return _b_search_pro(value, arr, left, mid-1)


def test_nornal_search(arr, test_arr):
    """测试普通查找算法"""
    result = []
    for value in test_arr:
        ret = find_it(arr, value)
        result.append((value, ret))

    return result



def test_binary_search(arr, test_data):
    """测试二分查找算法"""
    arr.sort()
    for item in test_data:
        value, ans = item
        result = binary_search(arr, value)
        if result != ans:
            print "error, value = {}".format(value)

def test_binary_search_pro(arr, test_data):
    """测试二分查找算法"""
    arr.sort()
    for item in test_data:
        value, ans = item
        result = binary_search_pro(arr, value)
        if result != ans:
            print "error, value = {}".format(value)


def time_func(func, **args):
    """测量时间"""
    t1 = time.time()
    func(**args)
    t2 = time.time()
    print 'func: {}, used_time: {}'.format(func.__name__, t2 - t1)


def test_search():
    args = sys.argv
    if len(args) < 3:
        print 'args error'
        sys.exit(1)

    filename = args[1]
    test_file = args[2]

    arr = load_nums(filename)
    test_data = load_lines(test_file);

    #time_func(test_nornal_search, arr=arr)
    #result = test_nornal_search(arr, test_data)
    #record_search_result('check.txt', result)
    #time_func(test_binary_search, arr=arr, test_data=test_data)
    time_func(test_binary_search_pro, arr=arr, test_data=test_data)

    print 'finished'


def make_nums():
    args = sys.argv
    if len(args) < 3:
        print 'args error'
        sys.exit(1)

    filename = args[1]
    n = int(args[2])
    create_nums(filename, n)


if __name__ == '__main__':
    # 676754
    test_search()
