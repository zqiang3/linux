def qsort(arr):
    left = 0
    right = len(arr) - 1
    #_qsort(arr, left, right)
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

        while low < high and  arr[low] < k:
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



def swap(arr, i, j):
    if i == j:
        return

    arr[j], arr[i] = arr[i], arr[j]

    
        
arr = [1, 3, 9, 2, 7, 11, 34]
qsort(arr)
print arr
