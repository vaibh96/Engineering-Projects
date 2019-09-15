#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<omp.h>
#include <time.h>
#include <math.h>
using namespace std;

void quickSort(int[],int,int);
int partition(int[],int,int);
 



int main(int argc, char *argv[])
{

	double dInitialTime, dFinalTime, dSerial=0, dParallel=0;
	 
	int DataSize = 0;
	
	
	int i, j, m, r;
	
	
		FILE *finput;
		finput = fopen("sortData1M.txt", "r");
		
		FILE *foutput;
		foutput = fopen("sorted.txt", "w");
		
		if (finput == NULL)
		{
			cout<<"Dataset file not found"<<endl;
			return(-1);
		}
		fscanf(finput, "%d", &DataSize);
		cout << "data size = " << DataSize << endl;
		int dataSet[DataSize];
		
		int input;
		
		for (int j = 0; j<DataSize; j++)
		{
			fscanf(finput, "%d", &input);
			dataSet[j] = input;
		}

	
	//int arr[]={}
	
		
		dInitialTime = omp_get_wtime();
		quickSort(dataSet, 0, DataSize-1);
		dFinalTime = omp_get_wtime();
		
		
		dParallel += dFinalTime-dInitialTime;
		cout<<"Time taken: "<<dParallel<<" By Parallel"<<endl;


	
	
	
	
	
	
	
	
	
		for (i = 0; i<DataSize; i++)
		{
			input=dataSet[i];
			fprintf(foutput, "%d", input);
			fprintf(foutput, "%s", "\n");
			
		}
		cout << endl;	
	
	return 0;
}

// Function to swap numbers 
void swap(int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  

int partition (int arr[], int l, int h) 
{ 
    int x = arr[h]; 
    int i = (l - 1); 
   #pragma omp parallel for
    for (int j = l; j <= h- 1; j++) 
    { 
        if (arr[j] <= x) 
        { 
            i++; 
            swap (&arr[i], &arr[j]); 
        } 
    } 
    swap (&arr[i + 1], &arr[h]); 
    return (i + 1); 
} 
  

void quickSort(int A[], int l, int h) 
{ 
    if (l < h) 
    {      
       
        int p = partition(A, l, h);  
        quickSort(A, l, p - 1);  
        quickSort(A, p + 1, h); 
    } 
      
} 
  
