// Merge sort code taken from: https://www.geeksforgeeks.org/merge-sort/

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
unsigned long long merge(int arr[], int l, int m, int r) 
{ 
    unsigned long long counter = 0;

    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
    {
        L[i] = arr[l + i]; 
        counter++;
    }
    for (j = 0; j < n2; j++) 
    {
        R[j] = arr[m + 1 + j]; 
        counter++;
    }
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) { 
        counter++;
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) { 
        counter++;
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) { 
        counter++;
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
    return counter;
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
unsigned long long mergeSort(int arr[], int l, int r) 
{ 
    unsigned long long counter = 0;

    if (l < r) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l + (r - l) / 2; 
  
        // Sort first and second halves 
        counter += mergeSort(arr, l, m); 
        counter += mergeSort(arr, m + 1, r); 
  
        counter += merge(arr, l, m, r); 
    } 

    return counter;
} 