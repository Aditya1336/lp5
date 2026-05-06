#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void printArray(vector<int> &arr)
{
  for (int i = 0; i < arr.size(); i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int partition(vector<int> &arr, int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++)
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

void quicksortSeq(vector<int> &arr, int low, int high)
{
  if (low < high)
  {
    int pivotIndex = partition(arr, low, high);
    quicksortSeq(arr, low, pivotIndex - 1);
    quicksortSeq(arr, pivotIndex + 1, high);
  }
}

void quickSortPara(vector<int> &arr, int low, int high)
{
  if (low < high)
  {
    int pivotIndex = partition(arr, low, high);
#pragma omp parallel sections
    {
#pragma omp section
      {
        quickSortPara(arr, low, pivotIndex - 1);
      }
#pragma omp section
      {
        quickSortPara(arr, pivotIndex + 1, high);
      }
    }
  }
}

int main()
{
  vector<int> arr = {12, 34, 531, 12, 35, 54, 2, 22, 48};

  vector<int> arr1 = arr;
  double secStart = omp_get_wtime();
  quicksortSeq(arr1, 0, arr1.size() - 1);
  double secEnd = omp_get_wtime();
  cout << "Sequential results ->>> " << endl;
  printArray(arr1);
  cout << "Time taken ->>> " << secEnd - secStart << "." << endl;

  vector<int> arr2 = arr;
  double secStart2 = omp_get_wtime();
  quickSortPara(arr2, 0, arr2.size() - 1);
  double secEnd2 = omp_get_wtime();
  cout << "Parallel results ->>> " << endl;
  printArray(arr2);
  cout << "Time taken ->>> " << secEnd2 - secStart2 << "." << endl;

  return 0;
}
