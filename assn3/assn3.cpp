#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <ctime>
#include <math.h>

using namespace std;
#define cols 1000
#define rows 1000
#define rowsPerThread 100
#define numThreads 10

int MAT1[cols][rows];
int MAT2[cols][rows];
int resSeq[cols][rows];
int resThr[cols][rows];

void *threadMultMat(void *p);

void printMat(int mat[rows][cols]){
	int x,y;
	for(x = 0; x < rows; x++)
		for(y = 0; y < cols; y++){
			cout << " " << mat[x][y];
			if(y==cols-1)
				cout << endl;
		}
}
int main(){
	struct timespec start, finish;
	double endSeq, endThr;
	//Initialize Matrixes for square matrices
	int x,y;

	//M1
	for(x = 0; x < rows; x++)
		for(y = 0; y < cols; y++){
			/*
			cout << "Enter value for M1[" << x << "][" << y << "]: ";
			cin >> MAT1[x][y];
			*/
			MAT1[x][y] = 9;
		}

	//M2
	for(x = 0; x < rows; x++)
		for(y = 0; y < cols; y++){
			/*
			cout << "Enter value for M2[" << x << "][" << y << "]: ";
			cin >> MAT2[x][y];
			*/
			MAT2[x][y] = 5;
		}

	//Sequential
	int i,j,k;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			for(k = 0; k < cols; k++){
				resSeq[i][j] += MAT1[i][k] * MAT2[k][j];
			}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	endSeq = (finish.tv_sec - start.tv_sec);
	endSeq += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	cout << "Sequential done" << endl;


	//Parralel/Threads
	clock_gettime(CLOCK_MONOTONIC, &start);
	pthread_t tid[numThreads];

    for (j=0;j<numThreads;j++)
        pthread_create(&tid[j],NULL,threadMultMat,(void*)j);

    for (j=0;j<numThreads;j++)
        pthread_join(tid[j],NULL);

	clock_gettime(CLOCK_MONOTONIC, &finish);
	endThr = (finish.tv_sec - start.tv_sec);
	endThr += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	cout << "Parrallel done" << endl;

	//Output times
	cout << "Seq: " << endSeq << " Thr: " << endThr << endl;
	double maxDiff=0; 
	/*
	printMat(resSeq);
	cout << endl;
	printMat(resThr);
	*/
	cout << endl;
	for(i=0; i<rows; i++){
		for(j = 0; j < cols; j++){
			if(fabs(resThr[i][j]-resSeq[i][j])>maxDiff) 
				maxDiff=fabs(resThr[i][j]-resSeq[i][j]); 
		}
	} 
	cout << "MaxDiff = " << maxDiff << endl;
	return 0;
}

void *threadMultMat(void *t)
{   
    int startRow;
    startRow = (intptr_t)t;
    startRow = rowsPerThread * startRow;

    int i,j,k;
    for (i = startRow;i<startRow + rowsPerThread;i++)
        for (j=0;j<cols;j++)
            for (k=0;k<rows;k++)
                resThr[i][j] += (MAT1[i][k] * MAT2[k][j]);
 }