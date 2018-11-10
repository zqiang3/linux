def qsort(arr):
    left = 0
    right = len(arr) - 1
    _qsort(arr, left, right)

def _qsort(arr, left, right):
    if left >= right:
        return

    k = arr[left]
    i, j = left, right + 1
    while i < j:
        i += 1
        while arr[i] < k:
            i += 1

        j -= 1
        while arr[j] > k:
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
