#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXBUFFER 1000

int main(int argc, char* argv[])
{

int n;
int fd[2];
pid_t pid;
char line[MAXBUFFER];
char line2[MAXBUFFER];
int j = 0;

if(pipe(fd) < 0)//create pipe
	printf("pipe error");
if((pid = fork()) < 0){ //create fork
	printf("fork error");
}else if(pid >0){//parent
	
	close(fd[0]);//close for reading
	while((fgets(line,MAXBUFFER,stdin)) != NULL){
		if(line[strlen(line)-1] == '\n'){
			line[strlen(line)-1] = 0;		
		}
	}
	write(fd[1],line,strlen(line));//write line to fd[1]
		
	
		
}else{//child
	close(fd[1]);//close for writing
			
	read(fd[0],line,MAXBUFFER);//read from parent
	for(int i = 0;i<MAXBUFFER;++i){
		if(line[i] != 'q'){
			line2[j] = line[i];
			++j;
		}
	}
	//write to stdout after removing q from buffer
	write(STDOUT_FILENO,line2,strlen(line2));
;
}

exit(0);
	
}
