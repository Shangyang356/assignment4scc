#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_VERTICE 875714
#define filename "directedgraph.txt"
#define listsize 30
FILE *fr;
long ptrarray[NUM_VERTICE][listsize];
int arraysize[NUM_VERTICE]; /*record the degree of each vertice in graph*/
long ptrarray2[NUM_VERTICE][listsize];
int arraysize2[NUM_VERTICE];/*record the degree of each vertice in reversed graph*/


int read(){
	char linebuff[20];
	char* buff;
	int start,end;
	int* size1;
	int* size2;
	fr = fopen (filename, "rt"); 
  	if (fr == NULL){
     	printf("can not open file \n");
     	return 1;
  	}
  	while(fgets(linebuff, 200, fr) != NULL)
  	{	
  		buff = strtok(linebuff, "\t");
  		sscanf (buff, "%d", &start);
  		buff = strtok(NULL,"\t");
  		sscanf(buff,"%d",&end);
  		size1 = &arraysize[start-1];
  		size2 = &arraysize2[end-1];
  		ptrarray[start-1][*size1] = end;
  		*size1 = *size1 + 1;
  		ptrarray[end-1][*size2] = start;
  		*size2 = *size2 + 1;;	
  	}
  	fclose(fr); 	
  	return 0;
}
int main(){
	read();
}