#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const auto timeLimit = chrono::hours(2);

short bubbleSort(int arr[], int n, chrono::high_resolution_clock::time_point time)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		if (chrono::high_resolution_clock::now() - time > timeLimit)
		{
			return (i * 100) / n;
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
short insertionSort(int arr[], int n, chrono::high_resolution_clock::time_point time)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		if (chrono::high_resolution_clock::now() - time > timeLimit)
		{
			return (i * 100) / n;
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
short mergeWrapper(int* arr, int size, chrono::high_resolution_clock::time_point time) {
	mergeSort(arr, 0, size - 1);
	return 100;
}
void timeFunction(short (*func)(int*, int, chrono::high_resolution_clock::time_point), string name, int size, string fileName) {
	int* arr = new int[size];
	importFile(arr, size, fileName);
	auto start = chrono::high_resolution_clock::now();
	short precentDone = func(arr, size, start);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
	delete[] arr;

	cout << "\t" << left << setw(21) << name + ":" << left << setw(10);
	if (precentDone == 100)
		cout << duration.count() / 1000000000.0 << "seconds" << endl;
	else
		cout << "Timed out (" << precentDone << "%)" << endl;
}

void heapify(int arr[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}
void heapsort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
short heapWrapper(int* arr, int size, chrono::high_resolution_clock::time_point time) {
	heapsort(arr, size);
	return 100;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}
void quicksort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}
short quickWrapper(int* arr, int size, chrono::high_resolution_clock::time_point time) {
	quicksort(arr, 0, size - 1);
	return 100;
}

void countingSort(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	int* count = new int[max + 1];
	for (int i = 0; i <= max; i++)
		count[i] = 0;
	for (int i = 0; i < n; i++)
		count[arr[i]]++;
	int index = 0;
	for (int i = 0; i <= max; i++)
		for (int j = 0; j < count[i]; j++)
			arr[index++] = i;
	delete[] count;
}
short countingWrapper(int* arr, int size, chrono::high_resolution_clock::time_point time) {
	countingSort(arr, size);
	return 100;
}

void radixSort(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	for (int exp = 1; max / exp > 0; exp *= 10)
		countingSort(arr, n);
}
short radixWrapper(int* arr, int size, chrono::high_resolution_clock::time_point time) {
	radixSort(arr, size);
	return 100;
}

void bucketSort(int arr[], int n) {
	// Find the maximum value in the array
	int max_val = arr[0];
	for (int i = 1; i < n; i++) {
		max_val = std::max(max_val, arr[i]);
	}

	// Create buckets based on the range of values (0 to max_val)
	int num_buckets = (max_val + 1);
	std::vector<std::vector<int>> buckets(num_buckets);

	// Scatter: Distribute elements into buckets
	for (int i = 0; i < n; i++) {
		int bucket_index = arr[i] / num_buckets;
		buckets[bucket_index].push_back(arr[i]);
	}

	// Sort elements in each bucket (you can choose any sorting algorithm here)
	for (int i = 0; i < num_buckets; i++) {
		std::sort(buckets[i].begin(), buckets[i].end());
	}

	// Gather: Combine sorted buckets back into the original array
	int j = 0;
	for (int i = 0; i < num_buckets; i++) {
		for (int val : buckets[i]) {
			arr[j++] = val;
		}
	}
}
short bucketWrapper(int* arr, int size, chrono::high_resolution_clock::time_point time) {
	bucketSort(arr, size);
	return 100;
}

struct File_Size
{
	string Filename;
	int Size;
};

struct Sorter
{
	string Name;
	short (*Sort)(int*, int, chrono::high_resolution_clock::time_point);
};

int main()
{
	const int HUNDRED_K = 100000;       //should be HUNDRED_K
	const int TEN_M = 10000000;			//should be TEN_M
	
	const size_t SORTCOUNT = 4;
	const size_t FILECOUNT = 6;
	File_Size files[FILECOUNT] = {
		{ "SortedRandomNumbersSmall.txt", HUNDRED_K },
		{ "RandomNumbersSmall.txt", HUNDRED_K },
		{ "ReversedRandomNumbersSmall.txt", HUNDRED_K },
		{ "SortedRandomNumbersLarge.txt", TEN_M },
		{ "RandomNumbersLarge.txt", TEN_M },
		{ "ReversedRandomNumbersLarge.txt", TEN_M }
	};
	Sorter sorts[SORTCOUNT] = {
		{ "Heap Sort", heapWrapper },
		{ "Quick Sort", quickWrapper },
		{ "Counting Sort", countingWrapper },
		{ "Bucket Sort", bucketWrapper}
	};

	for (size_t i = 0; i < FILECOUNT; i++)
	{
		cout << files[i].Filename << ": " << endl;
		for (size_t j = 0; j < SORTCOUNT; j++)
		{
			timeFunction(sorts[j].Sort, sorts[j].Name, files[i].Size, "../Data/" + files[i].Filename);
		}
	}
}
