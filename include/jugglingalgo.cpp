#include <iostream>

using namespace std;

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

void ArrayRotate(int A[], int n, int k)
{
  k=k%n;
  int d = -1, i, temp, j;
  for (i = 0; i < gcd(n, k); i++)
  {
    j = i;
    temp = A[i];
    while (1)
    {
      d = (j + k) % n;
      if (d == i)
        break;
      A[j] = A[d];
      j = d;
    }
    A[j] = temp;
  }
}

void displayArray(int A[], int n)
{
  int i;
  for (i = 0; i < n; i++)
    cout << A[i] << " ";
  cout << "\n";
}

int main()
{
  int n, i, k;
  cout << "Enter size of the Array\n";
  cin >> n;
  int A[n];
  cout << "Enter Array elements\n";
  for (i = 0; i < n; i++)
    cin >> A[i];
  cout << "Enter the value of k\n";
  cin >> k;
  displayArray(A, n);
  ArrayRotate(A, n, k);
  displayArray(A, n);
  return 0;
}