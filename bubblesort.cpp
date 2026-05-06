#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void bubblesort(vector<int> &arr)
{
  int n = arr.size();
  for (int i = 0; i < n; i++)
  {

#pragma omp parallel for
    for (int j = 0; j < n - 1; j += 2)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(arr[j], arr[j + 1]);
      }
    }

#pragma omp parallel for
    for (int j = 1; j < n - 1; j += 2)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

int main()
{
  vector<int> arr = {12, 11, 67, 34, 90, 46, 28, 289, 86};

  bubblesort(arr);

  for (int i = 0; i < arr.size(); i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}