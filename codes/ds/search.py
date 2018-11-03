#coding: utf-8
import sys
import random
import time
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



def load_nums(filename):
    """从文件载入数字"""
    arr = []
    f = open(filename, 'r')
    for line in f:
        arr.append(int(line))

    return arr


def find_it(arr, value):
    """普通查找算法"""
    if not isinstance(arr, list):
        return False

    for i in arr:
        if i == value:
            return True

    return False


def binary_search(arr, value):
    """二分查找算法"""
    return _b_search(value, arr, 0, len(arr) - 1)


def _b_search(value, arr, left, right):
    if left > right:
        return False

    mid = (left + right) / 2
    mid_value = arr[mid]
    if value == mid_value:
        return True
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


def test_nornal_search(arr):
    """测试普通查找算法"""
    for i in xrange(TEST_NUM):
        value = random.randint(0, MAX)
        result = find_it(arr, value)
        print 'value: {}, found: {}'.format(value, found)


def test_binary_search(arr):
    """测试二分查找算法"""
    for i in xrange(TEST_NUM):
        value = random.randint(0, MAX)
        result = binary_search(arr, value)
        #print 'value: {}, found: {}'.format(value, result)

def test_binary_search_pro(arr):
    """测试二分查找算法"""
    for i in xrange(TEST_NUM):
        value = random.randint(0, MAX)
        result = binary_search_pro(arr, value)
        #print 'value: {}, found: {}'.format(value, result)


def time_func(func, **args):
    """测量时间"""
    t1 = time.time()
    func(**args)
    t2 = time.time()
    print 'func: {}, used_time: {}'.format(func.__name__, t2 - t1)


def test_search():
    args = sys.argv
    if len(args) < 2:
        print 'args error'
        sys.exit(1)

    filename = args[1]

    arr = load_nums(filename)
    arr.sort()

    #time_func(test_nornal_search, arr=arr)
    time_func(test_binary_search_pro, arr=arr)
    time_func(test_binary_search, arr=arr)

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
    test_search()
    
