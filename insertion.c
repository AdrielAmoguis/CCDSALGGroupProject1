/* 
Retrived from: https://www.geeksforgeeks.org/insertion-sort
*/

/* Function to sort an array using insertion sort*/
unsigned long long insertionSort(int arr[], int n) 
{ 
	int i, key, j; 
	unsigned long long counter = 0;
	
	for (i = 1; i < n; i++) { 
		counter += 1;
		key = arr[i]; 
		j = i - 1; 

		/* Move elements of arr[0..i-1], that are 
		greater than key, to one position ahead 
		of their current position */
		while (j >= 0 && arr[j] > key) { 
			counter += 1;
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		} 
		arr[j + 1] = key; 
	} 
	return counter;
} 