#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;

const auto timeLimit = chrono::seconds(10);

short bubbleSort(int arr[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
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
short insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
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
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1; // size of left subarray
	int n2 = r - m; // size of right subarray
	
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
void mergeSort(int arr[], int l, int r)
{
	if (l >= r)
		return;
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}
void importFile(int arr[], int n, string fileName)
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
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
short mergeWrapper(int* arr, int size) {
	mergeSort(arr, 0, size - 1);
	return 100;
}
void timeFunction(short (*func)(int*, int), string name, int size, string fileName) {
	int* arr = new int[size];
	importFile(arr, size, fileName);
	auto start = chrono::high_resolution_clock::now();
	short precentDone = func(arr, size);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
	delete[] arr;

	cout << "\t" << left << setw(21) << name + ":" << left << setw(10);
	if (precentDone == 100)
		cout << duration.count() / 1000000000.0 << "seconds" << endl;
	else
		cout << "Timed out(" << precentDone << "%)" << endl;
}

int main()
{
	const int HUNDRED_K = 100000;       //should be HUNDRED_K
	const int TEN_M = 10000000;			//should be TEN_M
	
	const size_t FILECOUNT = 6;
	string files[6] = {
		"SortedRandomNumbersSmall.txt",
		"RandomNumbersSmall.txt",
		"ReversedRandomNumbersSmall.txt",
		"SortedRandomNumbersLarge.txt",
		"RandomNumbersLarge.txt",
		"ReversedRandomNumbersLarge.txt"
	};
	string names[3] = { "Merge Sort", "Insertion Sort", "Bubble Sort" };
	size_t sizes[6] = { HUNDRED_K, HUNDRED_K, HUNDRED_K, TEN_M, TEN_M, TEN_M };
	short (*sorts[3])(int*, int) = { mergeWrapper, insertionSort, bubbleSort };

	//timeFunction(mergeWrapper, "Merge Sort", HUNDRED_M, "../Data/RandomNumbersLarge.txt");
	//timeFunction(sorts[0], "Merge Sort", TEN_M, "../Data/RandomNumbersLarge.txt");

	for (size_t i = 0; i < FILECOUNT; i++)
	{
		cout << files[i] << ": " << endl;
		for (size_t j = 0; j < 3; j++)
		{
			timeFunction(sorts[j], names[j], sizes[i], "../Data/" + files[i]);
		}
	}
}
