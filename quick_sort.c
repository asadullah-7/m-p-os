#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void swap(int* a, int* b) {int t = *a; *a = *b; *b = t;}

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low, j = high;

    while(i<j)
    {
        while(arr[i] <= pivot) i++;
        while(arr[j] > pivot) j--;

        if(i<j) swap(&arr[i],&arr[j]);
    }
    swap(&arr[low],&arr[j]);
    return j;
}

void quicksort(int arr[], int low, int high)
{
    int pi;
    if(low < high)
    {
        pi = partition(arr,low,high);
        quicksort(arr,low,pi-1);
        quicksort(arr,pi+1,high);    
    }
    
}

int main(int argc, char* argv[])
{
    if(argc != 11)
    {
        printf("Enter 10 numbers %s",argv[0]);
        return 1;
    }

    int arr[10];
    for(int i = 0 ; i < 10; i++)
    {
        arr[i] = atoi(argv[i+1]);
    }

    quicksort(arr,0,10);
    for(int i = 0 ; i < 10; i++)
    {
        printf("%d,",arr[i]);
    }
    printf("\n\n");
    return 0;
}
