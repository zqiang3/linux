import struct
import traceback

MAX = 1000

def qsort(arr):
    left = 0
    right = len(arr) - 1
    _sort(arr, left, right)

def qsort_v2(arr):
    left = 0
    right = len(arr) - 1
    _qsort_v2(arr, left, right)

def _qsort_v2(arr, left, right):
    if left >= right:
        return

    k = arr[left]
    low = left
    high = right
    while low < high:
        while low < high and  arr[high] >= k:
            high -= 1
        arr[low] = arr[high]

        while low < high and  arr[low] <= k:
            low += 1
        arr[high] = arr[low]

    arr[low] = k

    _qsort_v2(arr, left, low - 1)
    _qsort_v2(arr, low + 1, right)


def _qsort(arr, left, right):
    if left >= right:
        return

    k = arr[left]
    i, j = left, right + 1
    while i < j:
        i += 1
        while i < right and arr[i] < k:
            i += 1

        j -= 1
        while j > left and  arr[j] > k:
            j -= 1

        if i < j:
            swap(arr, i, j)
            

    swap(arr, left, j)

    _qsort(arr, left, j - 1)
    _qsort(arr, i, right)


def _sort(arr, left, right):
    if left >= right:
        return

    k = arr[left]
    i, j = left, right
    while i < j:
        while i < j and arr[i] <= k:
            i += 1

        while j > left and arr[j] >= k:
            j -= 1

        if i < j:
            swap(arr, i, j)

    swap(arr, left, j)
    _sort(arr, left, j - 1)
    _sort(arr, i, right)



def swap(arr, i, j):
    if i == j:
        return

    arr[j], arr[i] = arr[i], arr[j]


def read_input(filename):
    output = list()
    f = open(filename, 'rb')
    count = 0
    while True:
        try:
            count += 1
            b_num = f.read(4)
            num = struct.unpack('i', b_num)
            output.append(num[0])
            if count > MAX:
                break
        except Exception as e:
            print 'error,', e
            print b_num
            print traceback.format_exc()
            break
    f.close()
    return output

def write_result(filename, arr):
    f = open(filename, 'w')
    for i in arr:
        f.write(str(i))
        f.write('\n')

    f.close()


    
def test_sort_func(func, fname):
    arr = read_input('numbers.txt')
    func(arr)
    write_result(fname, arr)

        

test_sort_func(qsort_v2, 'result2')
test_sort_func(qsort, 'result1')


