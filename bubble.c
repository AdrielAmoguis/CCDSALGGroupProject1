/*
	Bubble sort algorithm retrieved from: https://www.geeksforgeeks.org/bubble-sort/
*/

// An optimized version of Bubble Sort 
unsigned long long bubbleSort(int arr[], int n) 
{ 
   int i, j;
   unsigned long long counter = 0;
   bool swapped; 
   for (i = 0; i < n-1; i++) 
   { 
     counter += 1;				// counter variable here
     swapped = false; 
     for (j = 0; j < n-i-1; j++) 
     { 
	counter += 1;				// counter variable here
        if (arr[j] > arr[j+1]) 
        { 
           swap(&arr[j], &arr[j+1]); 
           swapped = true; 
        } 
     } 
  
     // IF no two elements were swapped by inner loop, then break 
     if (swapped == false) 
        break; 
   } 
   return counter;
} 