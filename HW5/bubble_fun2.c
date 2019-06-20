//functions for bubble sort
//Ryan Bornhorst
//ECE399- HW5

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

//function that does a bubble sort for the threads when
//the arrays are split into 4 equal parts
void* bubb_sort(void *arg){

int n = 16000;//size of array
int* bubble;
int temp;
bubble = (int*)arg;//value that the threads reference

for(int x = 0;x<(n-1);++x){//bubble sort
	for(int y = 0;y<n-x-1;++y){
		if(bubble[y] > bubble[y+1]){
			temp = bubble[y];
			bubble[y] = bubble[y+1];
			bubble[y+1] = temp;
		}
	}
}
return NULL;
}
//function that does a bubble sort for a single thread
//with an array of size 64,000
int bubb_sort_sing(int bubble[],int size){

int n = size;

int temp;
printf("\nHold on, we are waiting for the single thread to bubble sort an " 
	"array of 64,000 ints! \n");
struct timeval start,end;//start timer
gettimeofday(&start,NULL);

for(int x = 0;x<(n-1);++x){//bubble sort
	for(int y = 0;y<n-x-1;++y){
		if(bubble[y] > bubble[y+1]){
			temp = bubble[y];
			bubble[y] = bubble[y+1];
			bubble[y+1] = temp;
		}
	}
}
gettimeofday(&end,NULL);//end timer
float tot_time;
tot_time = ((end.tv_sec*1000000+end.tv_usec)
	   -(start.tv_sec*1000000+start.tv_usec));
tot_time = tot_time/1000000;

for(int i = 0;i<64000-1;++i){//check if in sorted order
	if(!(bubble[i] <= bubble[i+1])){
		printf("Not in Sorted Oder!\n");
		break;
	}else{
		printf("Sort Complete!\n");
		break;
	}
}
	
printf("Time of execution for single thread in seconds: %f \n",tot_time);

return 0;
}


//funtion that parses the original array into 4 equal partitions
int bub_parse(int bubble[],int bub1[],int bub2[],int bub3[],int bub4[],int size){

for(int i=0;i<size;++i)//first quarter of large array
	bub1[i] = bubble[i];

for(int i = size;i<size*2;++i)//second quarter
	bub2[i-size] = bubble[i];

for(int i = size*2;i<size*3;++i)//third quarter
	bub3[i-(size*2)] = bubble[i];

for(int i = size*3;i<size*4;++i)//last quarter
	bub4[i-(size*3)] = bubble[i];

return 0;
}


//function that merges 2 of the size 16,000 arrays into
//1 array of size 32,000
int bub_merge(int bub1[],int bub2[],int bub_new[]){

int size = 32000;

for(int i=0;i<size;++i)
	bub_new[i] = bub1[i];

for(int i=0;i<size-16000;++i)
	bub_new[i+16000] = bub2[i];

return 0;

}

//function that merges 2 of the size 32,000 arrays into 1
// array of size 64,000
int bub_merge2(int bub1[],int bub2[],int bub_new[]){

int size = 64000;

for(int i =0;i<size;++i)
	bub_new[i] = bub1[i];

for(int i = 0;i<size -32000;++i)
	bub_new[i+32000] = bub2[i];

return 0;
}
