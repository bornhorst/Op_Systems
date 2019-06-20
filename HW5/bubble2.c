//bubble sort algorithm with threads
//Ryan Bornhorst
//ECE399 - HW5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define BUF 64000
int bubble[BUF];
#define SIZE 16000//set up smaller arrays
int bub1[SIZE],bub2[SIZE],bub3[SIZE],bub4[SIZE];
int bubm1[32000],bubm2[32000];
int bubm_final[64000];//final array after threading


void* bubb_sort(void*arg);
void* bubb_sort2(void*arg);
void* bubb_sort3(void*arg);
int bub_parse(int bubble[],int bub1[],int bub2[],int bub3[],int bub4[],int size);
int bub_merge(int bub1[],int bub2[],int bub_new[]);
int bub_merge2(int bub1[],int bub2[],int bub_new[]);
int bubb_sort_sing(int bubble[],int size);

int main(int argc, char*argv[]){
srand(time(NULL));//random seed
for(int i = 0;i<BUF;++i)//create array of random ints
	bubble[i] = rand()%10000;//makes it random

/*
for(int i = 0;i<BUF;++i)//print original array
	printf("%d ",bubble[i]);
printf("\n");
*/

//splite bubble array into 4 equal chunks
bub_parse(bubble,bub1,bub2,bub3,bub4,SIZE);

printf("\nHold on, we are waiting for multiple threads to bubble"
	" sort an array of 64,000 ints! \n");
struct timeval start,end;
gettimeofday(&start,NULL);//start counting

pthread_t p1,p2,p3,p4,p5,p6,p7;//do the sort for the 4 seperate pieces
pthread_create(&p1,NULL,&bubb_sort,&bub1);//create threads
pthread_create(&p2,NULL,&bubb_sort,&bub2);
pthread_create(&p3,NULL,&bubb_sort,&bub3);
pthread_create(&p4,NULL,&bubb_sort,&bub4);

pthread_join(p1,NULL);//wait for threads to finish
pthread_join(p2,NULL);
pthread_join(p3,NULL);
pthread_join(p4,NULL);

//merge arrays first time
//bub_merge(bub1,bub2,bubm1);
//bub_merge(bub3,bub4,bubm2);

pthread_create(&p5,NULL,&bubb_sort2,&bubm1);//sort the new arrays
pthread_create(&p6,NULL,&bubb_sort2,&bubm2);

pthread_join(p5,NULL);//wait for threads to finish
pthread_join(p6,NULL);

//merge arrays second time
//bub_merge2(bubm1,bubm2,bubm_final);//merge arrays into single array

pthread_create(&p7,NULL,&bubb_sort3,&bubm_final);

pthread_join(p7,NULL);

gettimeofday(&end,NULL);//stop timer
float tot_time;
tot_time = ((end.tv_sec*1000000+end.tv_usec)
	   -(start.tv_sec*1000000+start.tv_usec));
tot_time = tot_time/1000000;

for(int i = 0;i<64000-1;++i){//check if in sorted order
	if(!(bubm_final[i] <= bubm_final[i+1])){
		printf("Not in Sorted Oder!\n");
		break;
	}else{
		printf("Sort Complete!\n");
		break;
	}
}
		
		
printf("Time of execution for multi-thread in seconds: %f \n",tot_time);



bubb_sort_sing(bubble,64000);//execute code with single thread


/*
for(int i = 0;i<64000;++i){
	printf("%d ",bubm_final[i]);
}
printf("\n");
*/


return 0;
}


//function that does a bubble sort for the threads when 
//the arrays are split into 2 equal parts
void* bubb_sort2(void *arg){


//merge arrays first time
bub_merge(bub1,bub2,bubm1);
bub_merge(bub3,bub4,bubm2);

int n = 32000;//size of array
int* bubble;
int temp;
bubble = (int*)arg;

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

//function that does a bubble sort for the threads when 
//there is only a single array of max size
void* bubb_sort3(void *arg){

bub_merge2(bubm1,bubm2,bubm_final);//merge arrays into single array

int n = 64000;//size of full array
int* bubble;
int temp;
bubble = (int*)arg;

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


