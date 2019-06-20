//Ryan Bornhorst

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFSIZE 10

void err_sys(char *msg){//print error message
	fprintf(stderr,"%s (%s) \n",msg,strerror(errno));
	exit(1);
}

int main(int argc, char *argv[])
{
	int n;
	int p= 0;
	int m = 0;
	int line;
	char buf[BUFFSIZE];
	if(argv[1] != NULL)//convert argv[1] to int 
		line = strtol(argv[1],NULL,10);
	else
		line = 1;//if no argv[1], then read 1 line

	while((m < line)&&(n = read(STDIN_FILENO, buf,BUFFSIZE))){
		for(int i = 0;i<BUFFSIZE;++i){
			if(buf[i] == '\n'){
				++m;//counter the number of new lines
				p = i+1;
			}
		}
		
	if(m < line){//write to console but dont overwrite to next line
		if(write(STDOUT_FILENO,buf,BUFFSIZE) != n)
			err_sys("write error");
	
	}
	}
	if((write(STDOUT_FILENO,buf,p)) != p)//write remaining buffer
		err_sys("write error");

	if(n<0)
		err_sys("read error");
	exit(0);
}

