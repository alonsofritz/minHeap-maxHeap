// A C++ program to demonstrate common Binary Heap Operations
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

/* A utility function to swap two elements */
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

/* A utility function to print array of size n */
void printArray(vector < int > & heapArray, int heapSize)
{
    for (int i = 0; i < heapSize; ++i)
        cout << heapArray[i] << ",";
    cout << "\n";
}

/* A recursive method to MinHeapify */
void minHeapify(vector < int > & heapArray, int heapSize, int i)
{
	int smallest = i;
	int l = i + ((i - (heapSize - 1)) - 1);
	int r = i + ((i - (heapSize - 1)) - 2);

	cout << smallest << " - " << l << " - " << r << endl;

	
    if (r > 0 && r < heapSize && heapArray[r] < heapArray[i]) {
		smallest = r;
	}
	if (l > 0 && l < heapSize && heapArray[l] < heapArray[smallest]) {
		smallest = l;
	}
	if (smallest != i) {
		swap(&heapArray[i], &heapArray[smallest]);
	
		minHeapify(heapArray, heapSize, smallest);
	}
}



/* A utility function to load file data */
bool getFileContent(string fileName, vector < int > & heapArray) {

    ifstream in (fileName);

    if (! in .is_open()) {
        cerr << "Cannot open the File : " << fileName << endl;
        return false;
    }

    int num;

    while ( in >> num) {
        heapArray.push_back(num);
    }

    in .close();

    return true;
}

/* A main function to the Heapsort */
void heapSort(vector < int > & heapArray, int heapSize)
{
    
    // POSSIVEL SOLUCAO: REALIZAR SOLUCAO E INVERTER A ORDEM

    // Build heap (rearrange array)
    for (int i = heapSize / 2 + 1; i < heapSize; i++) {
        minHeapify(heapArray, heapSize, i);
	}

	// Call printArray to see the state of the heap after MinHeapify execution
	 cout << "heapified : ";
     printArray(heapArray, heapSize);
  
    /*// One by one extract an element from heap
    for (int i = 0; i < heapSize - 1; i++) {
        
        
        cout << "heapsort: " << heapArray[i] << " - " << heapArray[heapSize - 1] << endl; 
        // Move current root to end
        swap(heapArray[i], heapArray[heapSize - 1]);
  
        // Call MinHeapify on the reduced heap
        minHeapify(heapArray, heapSize - i, heapSize - 1);
    }*/

    int i = 0;

    while(i < heapSize - 1) {
        cout << "Antes :";
        printArray(heapArray, heapSize);
        swap(heapArray[i], heapArray[heapSize - 1]);
        
        cout << "Depois :";
        printArray(heapArray, heapSize);
        ++i;
        minHeapify(heapArray, heapSize - i, heapSize - 1);
    }
}

// Driver program to test above functions
int main()
{
	ofstream csvFile;
    csvFile.open("resultsHeapSortMinHeap.csv");

    const int numTests = 1;
    const string path = "../Utils/BasicTest";

    for (const auto & entry: fs::directory_iterator(path)) {

        csvFile << (entry.path().string()).substr(path.length() + 1) << ", ";

        for (int countState = 0; countState < numTests; countState++) {

            vector < int > heapArray;
            getFileContent(entry.path().string(), heapArray);
            int heapSize = heapArray.size();

            auto start = std::chrono::high_resolution_clock::now();
			
			heapSort(heapArray, heapSize);

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration < double, std::milli > float_ms = end - start;

			// Call printArray post heapsort
			 printArray(heapArray, heapSize);

            csvFile << float_ms.count() << ", ";
        }

        csvFile << "\n";

    }

    cout << "Execution Completed Successfully!!" << endl;

	csvFile.close();

	return 0;
}