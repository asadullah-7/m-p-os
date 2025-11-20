#include <stdio.h>
#include <stdlib.h>

// Utility function to print array
void printArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 1️⃣ Bubble Sort
void bubbleSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

// 2️⃣ Selection Sort
void selectionSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        int min_idx = i;
        for(int j=i+1; j<n; j++)
            if(arr[j] < arr[min_idx])
                min_idx = j;
        int tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

// 3️⃣ Insertion Sort
void insertionSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        int key = arr[i];
        int j = i-1;
        while(j>=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// 4️⃣ Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m-l+1;
    int n2 = r-m;
    int L[n1], R[n2];

    for(int i=0; i<n1; i++) L[i] = arr[l+i];
    for(int i=0; i<n2; i++) R[i] = arr[m+1+i];

    int i=0, j=0, k=l;
    while(i<n1 && j<n2) {
        if(L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
    //8 3 5 4 7 6 1 2
}

void mergeSort(int arr[], int l, int r) {
    if(l<r) {
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// 5️⃣ Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low-1;
    for(int j=low; j<high; j++) {
        if(arr[j] <= pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j]; 
            arr[j] = tmp;
        }
    }
    int tmp = arr[i+1]; 
    arr[i+1] = arr[high]; 
    arr[high] = tmp;

    return i+1;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

// 6️⃣ Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;

    if(l<n && arr[l]>arr[largest]) largest = l;
    if(r<n && arr[r]>arr[largest]) largest = r;

    if(largest != i) {
        int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for(int i=n/2-1; i>=0; i--) heapify(arr, n, i);
    for(int i=n-1; i>0; i--) {
        int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;
        heapify(arr, i, 0);
    }
}

// Main to test all
int main() {
    int arr1[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr1)/sizeof(arr1[0]);

    int arr2[n], arr3[n], arr4[n], arr5[n], arr6[n];
    for(int i=0;i<n;i++){
        arr2[i]=arr3[i]=arr4[i]=arr5[i]=arr6[i]=arr1[i];
    }

    printf("Original array: ");
    printArray(arr1,n);

    bubbleSort(arr1,n);
    printf("Bubble Sort: ");
    printArray(arr1,n);

    selectionSort(arr2,n);
    printf("Selection Sort: ");
    printArray(arr2,n);

    insertionSort(arr3,n);
    printf("Insertion Sort: ");
    printArray(arr3,n);

    mergeSort(arr4,0,n-1);
    printf("Merge Sort: ");
    printArray(arr4,n);

    quickSort(arr5,0,n-1);
    printf("Quick Sort: ");
    printArray(arr5,n);

    heapSort(arr6,n);
    printf("Heap Sort: ");
    printArray(arr6,n);

    return 0;
}
