#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// ---------------------------------------------------
// Merge Function
// ---------------------------------------------------

void merge(vector<int> &arr, int left, int mid, int right)
{

  int n1 = mid - left + 1;
  int n2 = right - mid;

  // Temporary arrays
  vector<int> L(n1);
  vector<int> R(n2);

  // Copy left half
  for (int i = 0; i < n1; i++)
  {

    L[i] = arr[left + i];
  }

  // Copy right half
  for (int j = 0; j < n2; j++)
  {

    R[j] = arr[mid + 1 + j];
  }

  int i = 0;
  int j = 0;
  int k = left;

  // Merge both arrays
  while (i < n1 && j < n2)
  {

    if (L[i] <= R[j])
    {

      arr[k] = L[i];
      i++;
    }
    else
    {

      arr[k] = R[j];
      j++;
    }

    k++;
  }

  // Remaining elements of left array
  while (i < n1)
  {

    arr[k] = L[i];

    i++;
    k++;
  }

  // Remaining elements of right array
  while (j < n2)
  {

    arr[k] = R[j];

    j++;
    k++;
  }
}

// ---------------------------------------------------
// Sequential Merge Sort
// ---------------------------------------------------

void sequentialMergeSort(vector<int> &arr,
                         int left,
                         int right)
{

  if (left >= right)
    return;

  int mid = (left + right) / 2;

  sequentialMergeSort(arr, left, mid);

  sequentialMergeSort(arr, mid + 1, right);

  merge(arr, left, mid, right);
}

// ---------------------------------------------------
// Parallel Merge Sort
// ---------------------------------------------------

void parallelMergeSort(vector<int> &arr,
                       int left,
                       int right)
{

  if (left >= right)
    return;

  int mid = (left + right) / 2;

#pragma omp parallel sections
  {

// Left half
#pragma omp section
    {
      parallelMergeSort(arr, left, mid);
    }

// Right half
#pragma omp section
    {
      parallelMergeSort(arr, mid + 1, right);
    }
  }

  // Merge sorted halves
  merge(arr, left, mid, right);
}

// ---------------------------------------------------
// Print Array
// ---------------------------------------------------

void printArray(vector<int> &arr)
{

  for (int x : arr)
  {

    cout << x << " ";
  }

  cout << endl;
}

// ---------------------------------------------------
// Main Function
// ---------------------------------------------------

int main()
{

  vector<int> original = {
      38, 27, 43, 3,
      9, 82, 10, 55};

  // -----------------------------------------------
  // Sequential Merge Sort
  // -----------------------------------------------

  vector<int> arr1 = original;

  double start = omp_get_wtime();

  sequentialMergeSort(arr1,
                      0,
                      arr1.size() - 1);

  double end = omp_get_wtime();

  cout << "Sequential Merge Sort:\n";

  printArray(arr1);

  cout << "Time: "
       << end - start
       << " seconds\n\n";

  // -----------------------------------------------
  // Parallel Merge Sort
  // -----------------------------------------------

  vector<int> arr2 = original;

  start = omp_get_wtime();

  parallelMergeSort(arr2,
                    0,
                    arr2.size() - 1);

  end = omp_get_wtime();

  cout << "Parallel Merge Sort:\n";

  printArray(arr2);

  cout << "Time: "
       << end - start
       << " seconds\n";

  return 0;
}