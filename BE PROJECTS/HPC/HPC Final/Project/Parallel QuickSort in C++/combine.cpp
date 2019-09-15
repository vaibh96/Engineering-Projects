#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<omp.h>
#include <time.h>
#include <math.h>
using namespace std;


int main(int argc, char *argv[])
{

	 
	 
	int DataSize = 0;
	
	
	int i, j, m, r;
	
	
		FILE *finput;
		finput = fopen("sortData2M.txt", "r");
		
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

	
	
	
	
	return 0;
}
