#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main()
{
  vector<int> arr = {10, 20, 30, 40, 50, 60, 7, 80, 90, 100};
  int n = arr.size();

  int minimum = arr[0];
  int maximum = arr[0];

  int sum = 0;
  double average;

#pragma omp parallel for reduction(min : minimum)
  for (int i = 0; i < n; i++)
  {
    if (arr[i] < minimum)
    {
      minimum = arr[i];
    }
  }

#pragma omp parallel for reduction(max : maximum)
  for (int i = 0; i < n; i++)
  {
    if (arr[i] > maximum)
    {
      maximum = arr[i];
    }
  }

#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++)
  {
    sum += arr[i];
  }

  average = (double)sum / n;

  cout << "Minimum = " << minimum << endl;
  cout << "Maximum = " << maximum << endl;
  cout << "Sum = " << sum << endl;
  cout << "Average = " << average << endl;

  return 0;
}