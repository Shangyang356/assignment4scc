#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "quicksort.h"
#define NUM_VERTICE 875714
#define filename "directedgraph.txt"
#define listsize 7000
FILE *fr;
long ptrarray[NUM_VERTICE][457];
int arraysize[NUM_VERTICE]; /*record the degree of each vertice in graph*/
long ptrarray2[NUM_VERTICE][6327];
int arraysize2[NUM_VERTICE];/*record the degree of each vertice in reversed graph*/
int explored[NUM_VERTICE];
long label;
long stack[NUM_VERTICE];
long scc;
long sccnumarray[NUM_VERTICE];
long scctotalnum;
int init(){
	long i;
	for( i = 0; i<NUM_VERTICE;i++){
		arraysize[i] = 0;
		arraysize2[i] = 0;
		sccnumarray[i] = 0;
	}
	scctotalnum = 0;
	return 0;
}

int initexplored(){
	long i;
	for(i=0;i<NUM_VERTICE;i++){
		explored[i] = 0;
	}
	return 0;
}

int DFS2(long vertice){
	explored[vertice-1] =1;
	scc ++;
	printf("%ld ",vertice );
	int i,j;
	int size = arraysize2[vertice-1];
	for(i = 0;i<size;i++){
		j = ptrarray2[vertice-1][i];
		if(explored[j-1] == 0){
			DFS2(j);
		}
	}
	return 0;
}

int DFS(long vertice){
	explored[vertice-1] = 1;
	int i,j;
	int size = arraysize[vertice-1];
	for(i = 0;i < size;i++){
		j = ptrarray[vertice-1][i];
		if(!explored[j-1]){
			DFS(j);
		}
	}
	stack[label++] = vertice;
	return 0;
}

int read(){
	clock_t start_t, end_t;
	start_t = clock();
	char linebuff[20];
	char* buff;
	long head = 0;
	long tail = 0;
	int* size1;
	int* size2;
	fr = fopen (filename, "rt"); 
  	if (fr == NULL){
     	printf("can not open file \n");
     	return 1;
  	}
  	while(fgets(linebuff, 30, fr) != NULL)
  	{	
  		buff = strtok(linebuff, " ");
  		sscanf (buff, "%ld", &head);
  		buff = strtok(NULL," ");
  		sscanf(buff,"%ld",&tail);
  		size1 = &arraysize[head-1];
  		size2 = &arraysize2[tail-1];
  		ptrarray[head-1][*size1] = tail;
  		*size1 = *size1 + 1;
  		ptrarray2[tail-1][*size2] = head;
  		*size2 = *size2 + 1;;
  	}
  	end_t = clock();
  	float total_t = 1.0*(end_t - start_t)/CLOCKS_PER_SEC;
	printf("total time is %f\n",total_t );

	fclose(fr);
  	 

  	return 0;
}

int firsttraversal(){
	long i ;
	for(i = 0; i < NUM_VERTICE;i++){
		if(explored[i] == 0){
			DFS(i+1);
		}
	}
	return 0;
}

int secondtraversal(){
	long i,vertice;
	for(i = NUM_VERTICE-1;i>=0;i--){
		vertice = stack[i];
		if(explored[vertice-1]==0){
			scc = 0;
			DFS2(vertice);
			if(scc >1){
				sccnumarray[scctotalnum++] = scc;
			}
			printf("\n");
		}
	}
	return 0;
}


int main(){
	init();
	initexplored();
	read();
	firsttraversal();
	initexplored();
	secondtraversal();
	quicksort(scctotalnum,sccnumarray);
	long i;
	long sum = 0;
	printf("xixi\n");
	for(i = 0;i<scctotalnum;i++){
		printf("%ld th scc is %ld\n",i+1, sccnumarray[i]);
		sum +=sccnumarray[i];
	}
	printf("sum is %ld\n",sum );
	/*
	int max1 = 0;
	int max2 = 0;
	int j;
	long index1;
	long index2;
	for(i = 0;i<NUM_VERTICE;i++){
		j = arraysize[i];
		if(j > max1){
			max1 = j;
			index1 = i+1;
		}
		j = arraysize2[i];
		if(j > max2){
			max2 = j;
			index2 = i+1;
		}
	}
	printf(" max1 is %d the index is %ld and max2 is %d the index is %ld\n",max1,index1 ,max2,index2);
	*/
	return 0;
}