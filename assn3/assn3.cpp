#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <ctime>

using namespace std;
#define cols 1000
#define rows 1000

int MAT1[cols][rows];
int MAT2[cols][rows];
int resSeq[cols][rows];
int resThr[cols][rows];

void *threadMultMat(void *p);

int main(){
	clock_t start;
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
			MAT1[x][y] = 5;
		}

	/*
	//Output M1
	cout << "Matrix 1: " << endl;
	for(x = 0; x < rows; x++)
		for(y = 0; y < cols; y++){
			cout << " " << MAT1[x][y];
			if(y==cols-1)
				cout << endl;
		}

	//Output M2
	cout << "Matrix 2: " << endl;
	for(x = 0; x < rows; x++)
		for(y = 0; y < cols; y++){
			cout << " " << MAT2[x][y];
			if(y==cols-1)
				cout << endl;
		}
	*/
	start = clock();

	//Sequential
	int i,j,k;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			for(k = 0; k < cols; k++){
				resSeq[i][j] += MAT1[i][k] * MAT2[k][j];
			}

	endSeq = (clock() - start) / (double) CLOCKS_PER_SEC;

	/*
	//Output result of sequential multiplication
	cout << "Seq Res: " << endl;
	for(x = 0; x < rows; x++)
		for(y = 0; y < cols; y++){
			cout << " " << resSeq[x][y];
			if(y==cols-1)
				cout << endl;
		}
	*/
	cout << "Sequential done" << endl;

	start = clock();
	//Parralel/Threads
	pthread_t tid;
	pthread_create(&tid, NULL, threadMultMat, NULL);

	for(i = 0; i < rows; i = i + 2)
		for(j = 0; j < cols; j++)
			for(k = 0; k < cols; k++){
				resThr[i][j] += MAT1[i][k] * MAT2[k][j];
			}

	endThr = (clock() - start) / (double) CLOCKS_PER_SEC;

	/*
	//Output thread/Parrallel matrix
	cout << "Parrallel Res: " << endl;
	for(x = 0; x < rows; x++)
		for(y = 0; y < cols; y++){
			cout << " " << resThr[x][y];
			if(y==cols-1)
				cout << endl;
		}
	*/
	cout << "Parrallel done" << endl;

	cout << "Seq: " << endSeq << " Thr: " << endThr << endl;
	return 0;
}

void *threadMultMat(void *p){
	int i,j,k;
	for(i = 1; i < rows; i = i + 2)
		for(j = 0; j < cols; j++)
			for(k = 0; k < cols; k++){
				resThr[i][j] += MAT1[i][k] * MAT2[k][j];
			}
	pthread_exit(NULL);
}