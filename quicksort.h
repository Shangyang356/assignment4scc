#include <stdio.h>
//file i/o to read txt file.
FILE *fr;

unsigned long comparisons;
long sorttimes;
long exchange(long *p1,long *p2){
  long temp = *p1;
  *p1 = *p2;
  *p2 = temp;
  return 1;
}

long getmedianof3(long *num1,long *num2,long *num3){

  if((*num1>=*num2 &&*num2>=*num3)||(*num3>=*num2 && *num2>=*num1)){
    exchange(num2,num1);
  }
  else if((*num2>=*num1 && *num1>=*num3)||(*num3>=*num1 && *num1>=*num2))
  {}
  else if((*num1>=*num3 &&*num3>=*num2)||(*num2>=*num3 && *num3>=*num1)){
    exchange(num3,num1);
  }
  return *num1;
}

long partition1(long *array,long size){
  long i,j,pivot;
  i = 1;
  pivot = array[0];

  for(j = 1;j < size; j++){
    if(array[j]<=pivot){
      exchange(array+j,array+i);
      i++;
    }
  }
  exchange(array,array+i-1);
  return i-1;
}

long partition2(long *array,long size){
  long i,j,pivot;
  i = 1;
  exchange(array,array+size-1);
  pivot = array[0];
  for(j = 1;j < size; j++){
    if(array[j]<pivot){
      exchange(array+j,array+i);
      i++;
    }
  }
  exchange(array,array+i-1);
  return i-1;
}

long partition3(long *array,long size){
  long i,j,pivot;
  i = 1;
  j = size -1;
  if(size % 2 == 0){
    pivot = getmedianof3(array,array+j,array+(size/2-1));
  }
  else{
    pivot = getmedianof3(array,array+j,array+size/2);
  }
  for(j = 1;j < size; j++){
    if(array[j]<pivot){
      exchange(array+j,array+i);
      i++;
    }
  }
  exchange(array,array+i-1);
  return i-1;
}

long quicksort(long size,long *array){
  long pivot;
  long i;
  if(size >1){
    pivot = partition1(array,size);
    comparisons += size -1;
  
    if(pivot>1){
      i = quicksort(pivot,array);
    }
    if(pivot <size-2){
      i = quicksort(size - pivot-1,array + pivot+1);
    }
  }
  return 1;
}

/*
long main () {
  // input array
  long input[10000];
  // buff to store each line's content.
  char linebuff[80];

  long i =0;


  fr = fopen ("a2.txt", "rt"); 
  if (fr == NULL){
     prlongf("can not open file \n");
     return 1;
  }
  while(fgets(linebuff, 80, fr) != NULL)
  {

  sscanf (linebuff, "%ld", &input[i]);

  i++;
  }
  comparisons = 0;
  sorttimes = 0;
  //sort the input array.
  i = quicksort(10000,input);

  //check the result.
  
  for(i=0;i<10000;i++){
     if(input[i] != i+1){
      prlongf("%ldth element is equal to %ld mistake!\n", i+1,input[i]);
     }
  }
  prlongf("the num of comparisons is %lu\n", comparisons);
  
  fclose(fr);  
  return 1;
}
*/