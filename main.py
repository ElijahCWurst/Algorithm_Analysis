def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        print(arr)
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j = j - 1
        arr[j + 1] = key
    return arr


def merge_sort(arr):
    n = len(arr)
    if n > 1:
        mid = n // 2
        left = arr[:mid]
        right = arr[mid:]
        merge_sort(left)
        merge_sort(right)
        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                arr[k] = left[i]
                k = k + 1
                i = i + 1
            else:
                arr[k] = right[j]
                k = k + 1
                j = j + 1
        while i < len(left):
            arr[k] = left[i]
            k = k + 1
            i = i + 1
        while j < len(right):
            arr[k] = right[j]
            k = k + 1
            j = j + 1
    return arr


# Array filled with 10 random numbers in between 1 and 50
Arr = [3, 7, 9, 2, 1, 4, 6, 5, 8, 10]
bubble_sort(Arr)