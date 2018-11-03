import random
import time
MAX = 100000
TEST_NUM = 10000

def create_nums(filename, n):
    f = open(filename, 'w')
    for i in xrange(n):
        num = random.randint(0, MAX)
        f.write(str(num))
        f.write('\n')

    f.close()


def find_it(arr, value):
    if not isinstance(arr, list):
        return False

    for i in arr:
        if i == value:
            return True

    return False

def binary_search(arr, value):
    return _b_search(value, arr, 0, len(arr) - 1)
    pass

def _b_search(value, arr, left, right):
    if left > right:
        return False

    mid = (left + right) / 2
    mid_value = arr[mid]
    if value == mid_value:
        return True
    elif value > mid_value:
        return _b_search(value, arr, mid+1, right);
    else:
        return _b_search(value, arr, left, mid-1);



def load_nums(filename):
    arr = []
    f = open(filename, 'r')
    for line in f:
        arr.append(int(line))

    return arr



def test_nornal_search(arr):
    for i in xrange(TEST_NUM):
        value = random.randint(0, MAX)
        result = find_it(arr, value)

def test_binary_search(arr):
    arr.sort()
    for i in xrange(TEST_NUM):
        value = random.randint(0, MAX)
        result = binary_search(arr, value)


def time_func(func, **args):
    t1 = time.time()
    func(**args)
    t2 = time.time()
    print 'used_time: {}'.format(t2 - t1)


if __name__ == '__main__':
    import sys
    if len(sys.argv) < 3:
        print 'args error'
        sys.exit(1)

    filename = sys.argv[1]
    n = sys.argv[2]
    #create_nums(filename, int(n))

    arr = load_nums(filename)

    time_func(test_nornal_search, arr=arr)
    time_func(test_binary_search, arr=arr)

    print 'finished'
