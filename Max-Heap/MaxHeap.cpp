// A C++ program to demonstrate common Binary Heap Operations
#include<iostream>
#include<climits>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

// A utility function to swap two elements
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// A class for max Heap
class MaxHeap
{
	int *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of max heap
	int heap_size; // Current number of elements in max heap
public:
	// Constructor
	MaxHeap(int capacity);

	// to heapify a subtree with the root at given index
	void MaxHeapify(int );

	int parent(int i) { return (i-1)/2; }

	// to get index of left child of node at index i
	int left(int i) { return (2*i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2*i + 2); }

	// to extract the root which is the minimum element
	int extractMin();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from max heap
	int getMin() { return harr[0]; }

	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k'
	void insertKey(int k);

	// Print Array
	void printArray();
};

// Constructor: Builds a heap from a given array a[] of given size
MaxHeap::MaxHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// Inserts a new key 'k'
void MaxHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	// Fix the max heap property if it is violated
	while (i != 0 && harr[parent(i)] < harr[i])
	{
	swap(&harr[i], &harr[parent(i)]);
	i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MaxHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(&harr[i], &harr[parent(i)]);
	i = parent(i);
	}
}

// Method to remove maximum element (or root) from max heap
int MaxHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the minimum value, and remove it from heap
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	MaxHeapify(0);

	return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MaxHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MaxHeap::MaxHeapify(int i)
{
	int l = left(i);
	int r = right(i);

	int largest = i;
	
    if (l < heap_size && harr[l] > harr[i])
		largest = l;
	if (r < heap_size && harr[r] > harr[largest])
		largest = r;
	if (largest != i)
	{
		swap(&harr[i], &harr[largest]);
		MaxHeapify(largest);
	}
}

/* A utility function to print array of size n */
void MaxHeap::printArray()
{
    for (int i = 0; i < heap_size; ++i)
        cout << harr[i] << ",";
    cout << "\n";
}

bool getFileContent(string fileName, vector < int > & data) {

    ifstream in (fileName);

    if (! in .is_open()) {
        cerr << "Cannot open the File : " << fileName << endl;
        return false;
    }

    int num;

    while ( in >> num) {
        data.push_back(num);
    }

    in .close();

    return true;
}

// Driver program to test above functions
int main()
{
	ofstream csvFile;
    csvFile.open("resultsMaxHeap.csv");

    const int numTests = 1;
    const string path = "../Utils/BasicTest";

    for (const auto & entry: fs::directory_iterator(path)) {

        csvFile << (entry.path().string()).substr(path.length() + 1) << ", ";

        for (int countState = 0; countState < numTests; countState++) {

            vector < int > data;
            getFileContent(entry.path().string(), data);
            int dataSize = data.size();

			MaxHeap h(dataSize);

            auto start = std::chrono::high_resolution_clock::now();
			for(int insertCount = 0; insertCount < dataSize; insertCount++){
				h.insertKey(data[insertCount]);
			}
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration < double, std::milli > float_ms = end - start;

			h.printArray();

            csvFile << float_ms.count() << ", ";
        }

        csvFile << "\n";

    }

    cout << "Execution Completed Successfully!!" << endl;

	csvFile.close();

	return 0;
}