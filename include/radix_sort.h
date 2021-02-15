/*
Radix sort
*/

int find_largest_number(int arr[], int n) {

  int i;
  int largest_number = -1;

  for (i = 0; i < n; i++) {
    if (arr[i] > largest_number) largest_number = arr[i];
  }

  return largest_number;
}

void radix_sort(int* arr, int n) {

  // Base 10 is used
  int i;
  int semi_sorted[n];
  int significant_digit = 1;
  int largest_number = find_largest_number(arr, n);

  // Loop until we reach the largest significant digit
  while (largest_number / significant_digit > 0) {


    int bucket[10] = {0};

    // Counts the number of "keys" or digits that will go into each bucket
    for (i = 0; i < n; i++) bucket[(arr[i] / significant_digit) % 10]++;

    /**
     * Add the count of the previous buckets,
     * Acquires the indexes after the end of each bucket location in the arr
     * Works similar to the count sort algorithm
     **/
    for (i = 1; i < 10; i++) bucket[i] += bucket[i - 1];

    // Use the bucket to fill a "semi_sorted" arr
    for (i = n - 1; i >= 0; i--)
      semi_sorted[--bucket[(arr[i] / significant_digit) % 10]] = arr[i];


    for (i = 0; i < n; i++) arr[i] = semi_sorted[i];

    // Move to next significant digit
    significant_digit *= 10;
  }
}
