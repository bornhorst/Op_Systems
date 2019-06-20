#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
struct timeval start,end;
gettimeofday(&start,NULL);//collect time

int fd[2];
pid_t pid;

if(pipe(fd) < 0)//create pipe
	printf("pipe error");
if((pid = fork()) < 0){//create fork
	printf("fork error");
}else if(pid >0){//parent

	wait(NULL);//wait for child
	gettimeofday(&end,NULL);//collect new time
	//subtract start time from end time.. convert to microseconds
	unsigned long tot_time = ((end.tv_sec*1000000 + end.tv_usec) 
		- (start.tv_sec*1000000 + start.tv_usec));
	printf("Time of execution in useconds: %ld \n",tot_time);

}else{//chile

	execlp(argv[1],argv[1],(char*)0);//execute program
	

}

exit(0);
}
