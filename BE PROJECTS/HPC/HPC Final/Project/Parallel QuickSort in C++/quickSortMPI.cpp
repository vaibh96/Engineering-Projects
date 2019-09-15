/*******************************

	parallel quicksort in C++ 
	Qingkui Wang
	3/10/2015

*******************************/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
using namespace std;

void paraQuickSort(int *dataSet, int left, int right, int m, int id, int CurrentID);
void quickSort(int *dataSet, int left, int right);
int partition(int *dataSet, int left, int right);

int main(int argc, char *argv[])
{
	int DataSize = 0;
	int *dataSet = NULL;
	int CurrentID, SumNum;
	int i, j, m, r;
	double starttime, endtime;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &CurrentID);
	MPI_Comm_size(MPI_COMM_WORLD, &SumNum);
	cout << "Process " << CurrentID << "/" << SumNum << endl;
	
	//read dataset file
	if (CurrentID == 0)
	{

		FILE *finput;
		//finput = fopen("sortData2M.txt", "r");
		//finput = fopen("sortData1M.txt", "r");
		finput = fopen("sortData2M.txt", "r");
		if (finput == NULL)
		{
			cout<<"Dataset file not found"<<endl;
			return(-1);
		}
		fscanf(finput, "%d", &DataSize);
		cout << "data size = " << DataSize << endl;
		dataSet = (int*)malloc(DataSize*sizeof(int));
		int input;
		for (int j = 0; j<DataSize; j++)
		{
			fscanf(finput, "%d", &input);
			dataSet[j] = input;
		}

	}

	starttime = MPI_Wtime();
	m = log2(SumNum);
	//cout << "m:" << m << endl;
	paraQuickSort(dataSet, 0, DataSize - 1, m, 0, CurrentID);
	/*
	//print the sorted dataset here
	if (CurrentID == 0)
	{
		for (i = 0; i<DataSize; i++)
		{
			cout << dataSet[i] << " ";
		}
		cout << endl;
	}
	*/ 
	endtime = MPI_Wtime();
	MPI_Finalize();
	cout << "Total time of " << CurrentID << " is " << endtime - starttime << endl;

	return 0;
}

/*********************************************
Function: void paraQuickSort(int *dataSet, int left, int right, int m, int id, int CurrentID)
Description: parallel quicksort using MPI
Input: dataSet: dataset to be sorted
	   left: the start point of the dataset
	   right: the end point of the dataset
	   m: log2(number of processes)
	   id: initial process id
	   CurrentID: current process id
Return: void
*********************************************/
void paraQuickSort(int *dataSet, int left, int right, int m, int id, int CurrentID)
{
	int i, j;
	int r = 0;
	int MyLength = -1;
	int *tmp = NULL;
	MPI_Status status;
	if (m == 0)
	{
		if (CurrentID == id)
			quickSort(dataSet, left, right);
		return;
	}

	if (CurrentID == id)
	{
		r = partition(dataSet, left, right);
		MyLength = right - r;
		MPI_Send(&MyLength, 1, MPI_INT, id + pow(2, (m - 1)), CurrentID, MPI_COMM_WORLD);
		//cout << "test here, "<< CurrentID << "MyLenght = " << MyLength << endl;
		if (MyLength != 0)
		{
			MPI_Send(dataSet + r + 1, MyLength, MPI_INT, id + pow(2, (m - 1)), CurrentID, MPI_COMM_WORLD);
		}

	}

	if (CurrentID == id + pow(2, (m - 1)))
	{
		MPI_Recv(&MyLength, 1, MPI_INT, id, id, MPI_COMM_WORLD, &status);
		if (MyLength != 0)
		{
			tmp = (int *)malloc(MyLength*sizeof(int));
			if (tmp == 0) perror("Malloc memory error!");
			MPI_Recv(tmp, MyLength, MPI_INT, id, id, MPI_COMM_WORLD, &status);
			//cout << "test R here, " << CurrentID << "r = " << r << endl;
		}
	}
	paraQuickSort(dataSet, left, r - 1, m - 1, id, CurrentID);
	paraQuickSort(tmp, 0, MyLength - 1, m - 1, id + pow(2, (m - 1)), CurrentID);

	if ((CurrentID == id + pow(2, (m - 1))) && (MyLength != 0))
		MPI_Send(tmp, MyLength, MPI_INT, id, id + pow(2,(m - 1)), MPI_COMM_WORLD);
	if ((CurrentID == id) && (MyLength != 0))
		MPI_Recv(dataSet + r + 1, MyLength, MPI_INT, id + pow(2, (m - 1)), id + pow(2, (m - 1)), MPI_COMM_WORLD, &status);
}

/*********************************************
Function: void quickSort(int *data, int start, int end)
Description: quicksort with recursion
Input: dataSet: dataset to be sorted
	   left: the start point of the dataset
       right: the end point of the dataset
Return: void
Others: recursion
*********************************************/
void quickSort(int *dataSet, int left, int right)
{
	int r;
	if (left < right)
	{
		r = partition(dataSet, left, right);
		quickSort(dataSet, left, r - 1);
		quickSort(dataSet, r + 1, right);
	}
}

/*********************************************
Function: int partition(int *data, int start, int end)
Description: divide array by the pivot
Input: dataSet: dataset to be sorted
	   left: the start point of the dataset 
	   right: the end point of the dataset 
Return: the partition position (int)
Others: pick the last element of the array as pivot
**********************************************/
int partition(int *dataSet, int left, int right)
{
	int pivot;
	int i, j;
	int tmp;
	pivot = dataSet[right];
	i = left - 1;
	for (j = left; j < right; j++)
	{
		if (dataSet[j] <= pivot)
		{
			i++;
			tmp = dataSet[i];
			dataSet[i] = dataSet[j];
			dataSet[j] = tmp;
		}
	}
	tmp = dataSet[i + 1];
	dataSet[i + 1] = dataSet[right];
	dataSet[right] = tmp;
	//cout << "I am here, partition!" << endl;
	return i + 1;

}
