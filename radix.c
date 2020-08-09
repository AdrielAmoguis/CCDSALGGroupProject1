// Radix sort from: https://www.geeksforgeeks.org/radix-sort/

// A utility function to get maximum value in arr[] 
int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
    {
        if (arr[i] > mx) 
            mx = arr[i]; 
    }
    return mx; 
} 
  
// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
unsigned long long countSort(int arr[], int n, int exp) 
{ 
    unsigned long long counter = 0;
    int output[n]; // output array 
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
    {
        counter++;
        count[ (arr[i]/exp)%10 ]++; 
    }
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
    {
        counter++;
        count[i] += count[i - 1]; 
    }
    
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    {
        counter++; 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
    {   
        counter++;
        arr[i] = output[i]; 
    }
    return counter;
} 
  
// The main function to that sorts arr[] of size n using  
// Radix Sort 
unsigned long long radixSort(int arr[], int n) 
{ 
    unsigned long long counter = 0;
    // Find the maximum number to know number of digits 
    int m = getMax(arr, n); 
    counter += n-1;
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= 10) 
        counter += countSort(arr, n, exp); 

    return counter;
} 