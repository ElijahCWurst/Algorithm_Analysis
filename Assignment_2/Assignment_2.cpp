#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;

const auto timeLimit = chrono::hours(2);

short bubbleSort(int arr[], size_t n, chrono::high_resolution_clock::time_point time)
{
    size_t i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        if (chrono::high_resolution_clock::now() - time > timeLimit)
        {
            return (short)((i * 100) / n);
        }
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    return 100;
}
short insertionSort(int arr[], size_t n, chrono::high_resolution_clock::time_point time)
{
    size_t i, j;
    int key;
    for (i = 1; i < n; i++)
    {
        if (chrono::high_resolution_clock::now() - time > timeLimit)
        {
            return (short)((i * 100) / n);
        }
        key = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
            
        }
        arr[j + 1] = key;
    }
    return 100;
}
void merge(int arr[], size_t l, size_t m, size_t r)
{
    size_t i, j, k;
    size_t n1 = m - l + 1; // size of left subarray
    size_t n2 = r - m; // size of right subarray
    
    //dynamically allocated temp arrays
    int *L = new int[n1];
    int *R = new int[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
        
    i = 0; // initial index of left subarray
    j = 0; // initial index of right subarray
    k = l; // initial index of merged subarray
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}
void mergeSort(int arr[], size_t l, size_t r)
{
    if (l >= r)
        return;
    size_t m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}
void importFile(int arr[], size_t n, string fileName)
{
    ifstream file;

    file.open(fileName);

    if (!file)
    {
        cout << "Unable to open file";
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        file >> arr[i];
    }

    file.close();
}
void printArray(int arr[], size_t n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}
short mergeWrapper(int* arr, size_t size, chrono::high_resolution_clock::time_point time) {

    mergeSort(arr, 0, size - 1);
    return 100;
}
void timeFunction(short (*func)(int*, size_t, chrono::high_resolution_clock::time_point), string name, size_t size, string fileName) {
    int* arr = new int[size];
    importFile(arr, size, fileName);
    auto start = chrono::high_resolution_clock::now();
    short precentDone = func(arr, size, start);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    delete[] arr; // free memory and prevent memory leaks

    cout << "\t" << left << setw(21) << name + ":";
    if (precentDone == 100)
        cout << left << setw(10) << duration.count() / 1000000000.0 << "seconds" << endl;
    else
        cout << left << setw(10) << "Timed out (" << precentDone << "%)" << endl;
}

int main()
{
    const int HUNDRED_K = 100000;       //should be HUNDRED_K
    const int TEN_M = 10000000;         //should be TEN_M
    
    const size_t FILECOUNT = 6;
    struct File
    {
        string FileName;
        int Size;
    };
    File files[6] = {
        { "SortedRandomNumbersSmall.txt", HUNDRED_K },
        { "RandomNumbersSmall.txt", HUNDRED_K },
        { "ReversedRandomNumbersSmall.txt", HUNDRED_K },
        { "SortedRandomNumbersLarge.txt", TEN_M },
        { "RandomNumbersLarge.txt", TEN_M },
        { "ReversedRandomNumbersLarge.txt", TEN_M }
    };
    struct Sorter
    {
        string Name;
        short (*Function)(int*, size_t, chrono::high_resolution_clock::time_point);
    };

    Sorter sorts[3] = {
        { "Merge Sort", mergeWrapper },
        { "Insertion Sort", insertionSort },
        { "Bubble Sort", bubbleSort }
    };
    for (size_t i = 0; i < FILECOUNT; i++)
    {
        cout << files[i].FileName << ": " << endl;
        for (size_t j = 0; j < 3; j++)
        {
            timeFunction(sorts[j].Function, sorts[j].Name, files[i].Size, "../Data/" + files[i].FileName);
        }
    }
}
