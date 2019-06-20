//Ryan Bornhorst
//ECE 399
//Shell Program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>

char*read_input(void);
char **get_parameters(char*command);
int count_params(char**parameters);
int exec_background(char*command,char **pararmeters);
char** get_command(int pos,char*command);
int make_num(char*parameters);
int exec_red(int num,char**parameters);
int exec_norm(char**parameters);
int exec_red2(int num,char**parameters);
int piper(int num,char**parameters);

int main(int argc,char *argv[]){
int shellcount = 1;
char* command;
char** parameters;
int num_lines = 0;
int com_num = 0;
char*command_line[5];
int flag = 0;
int m;
int flag2;

while(1){

flag2 = 0;//set flag
printf("MY_SHELL[%d]~$ ",shellcount);
command = read_input();//read from user
if(com_num == 5){
	flag = 1;//set flag
	com_num = 0;
}
command_line[com_num] = command;//store command
++com_num;

parameters =get_parameters(command);//parse command
int count = count_params(parameters);//count args

m = 0;
while(parameters[m] != NULL){
	if((strcmp(parameters[m],"<"))==0){
		exec_red(m,parameters);//redirect to input
		flag2 = 1;
	}else if((strcmp(parameters[m],">"))==0){
		exec_red2(m,parameters);//redirect to output
		flag2 = 1;
	}else if((strcmp(parameters[m],"|"))==0){
		piper(m,parameters);
		flag2 = 1;
	++m;
}

if((strcmp(parameters[count-1],"&"))==0)
	exec_background(command,parameters);//run background

if((parameters[0][0])=='!'){//execute numbered command
	int number = make_num(parameters[0]);
	if(number < 5 && number > 0)
		printf("Execute Command: %s \n",command_line[number-1]);
		exec_norm(get_parameters(command_line[number-1]));
		
		flag2 = 1;//set flag
}

if((strcmp(parameters[0],"exit")) ==0)
	return 0;//exit shell

if((strcmp(parameters[0],"history")) == 0){//show last five command
	printf("These are the most recent 5 commands:\n");
	flag2 = 1;
	if(flag == 0){
		for(int i = 0;i<com_num;++i){
			printf("[%d] %s \n",i+1,command_line[i]);
		}
	}
	if(flag == 1){//show if more than five
		for(int i = 0;i<5;++i){
			printf("[%d] %s \n",i,command_line[i]);
		}
	}
}
if(flag2 == 0)
	exec_norm(parameters);//execute commande if no special arguments		

//increment counters
++num_lines;
++shellcount;
}
//free memory
free(command);
free(parameters);

}
