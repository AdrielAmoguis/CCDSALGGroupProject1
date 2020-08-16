/*
Retrieved from: https://www.geeksforgeeks.org/selection-sort
*/

unsigned long long selectionSort(int arr[], int n) 
{ 
	int i, j, min_idx; 
	unsigned long long counter = 0;
	
	// One by one move boundary of unsorted subarray 
	for (i = 0; i < n-1; i++) 
	{ 
		counter += 1;
		// Find the minimum element in unsorted array 
		min_idx = i; 
		for (j = i+1; j < n; j++) 
		{
			counter += 1;
			if (arr[j] < arr[min_idx]) 
				min_idx = j; 
		}

		// Swap the found minimum element with the first element 
		swap(&arr[min_idx], &arr[i]); 
	} 
	return counter;
} 
