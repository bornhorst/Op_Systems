//Ryan Bornhorst
//Functions for the shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

//reads line of input from the user
//returns line as pointer to char array
char *read_input(void){

char * input = NULL;
//buffersize is set by input from user
ssize_t buffersize = 0;
getline(&input,&buffersize,stdin);
return input;

}


//takes user input and seperates it into arguments
//basically makes char* argv[] parameters
//returns pointer to array of char arrays
char**get_parameters(char*command){

int buffersize = 100;//set up buffsize
int i = 0;
char**parameters = malloc(buffersize*sizeof(char*));
char*newcommand = malloc((strlen(command)+1)*sizeof(char*));
strcpy(newcommand,command);
char *parameter;

//seperate parameters using these delimeters 
//space, tab, or endline
parameter = strtok(newcommand," \t\n");

while(parameter != NULL){
	parameters[i] = parameter;//assign argv[i]
	++i;

	//if more buffer is needed, double the buffersize
	if(i >= buffersize){
		buffersize = buffersize +100;
		parameters = realloc(parameters,buffersize*sizeof(char*));
		if(parameters == NULL){
			printf("Parameter Buffer Error\n");
			exit(1);
		}
	}

//puts null in between parameters
parameter = strtok(NULL," \t\n");

}
//parameters[i] = NULL;//make sure that array terminates with NULL
return parameters;

}

int count_params(char**parameters){
	int i = 0;
	while(parameters[i] != NULL)
		++i;
	
return i;
}

//function that executes a background process
int exec_background(char*command,char**parameters){

pid_t pid;
pid = fork();

if(pid < 0){
	printf("Fork Error\n");
}else if(pid == 0){
	setsid();
	chdir("/");//root
	umask(0);
	close(STDIN_FILENO);//close files
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if((execvp(parameters[0],parameters)) < 0)
		printf("Execute Error\n");
	exit(1);
}else {
	wait(NULL);//wait for child
	printf("DONE: %s \n",command);
}
return 0;
}

//function that makes a parameter into
//an integer
int make_num(char*parameters){
	int size = strlen(parameters);
	char newpar[size];
	for(int i = 0;i<size;++i){
		newpar[i] = parameters[i+1];
	}
	return atoi(newpar);//make an int
	
}
//function that redirects output to a file
//only works for simple command > filename
int exec_red(int num,char**parameters){

pid_t pid;
pid = fork();
if(pid == 0){//child
	close(STDOUT_FILENO);//close stdout
	open(parameters[num+1],O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
	char* myargs[num +1];//open 
	for(int i = 0;i<num;++i)
		myargs[i] = parameters[i];
	myargs[num] = NULL;

	if((execvp(myargs[0],myargs))< 0)
		printf("Execution Error\n");
	exit(1);
}else if(pid < 0){
	printf("Fork Error\n");
}else{//parent
	wait(NULL);//wait for child
}
return 0;

}
//function that redirects file output to command stdin
int exec_red2(int num,char**parameters){
int status;
pid_t pid,wpid;
pid = fork();
if(pid == 0){//child
	close(STDIN_FILENO);//close stdin
	open(parameters[num+1],O_RDONLY);//read only
	char* myargs[num +1];
	for(int i = 0;i<num;++i)
		myargs[i] = parameters[i];
	myargs[num] = NULL;

	if((execvp(myargs[0],myargs))< 0)
		printf("Execution Error\n");
	exit(1);
}else if(pid < 0){
	printf("Fork Error\n");
}else{//parent
	wpid = waitpid(pid,&status,WUNTRACED);//wait for child
}
return 0;

}

//function that does a basic execution
int exec_norm(char**parameters){

pid_t pid,wpid;
int status;
pid = fork();
if(pid == 0){//child
	if((execvp(parameters[0],parameters))< 0)
		printf("Execution Error\n");
	exit(1);
}else if(pid < 0){
	printf("Fork Error\n");
}else{//parent
	wpid = waitpid(pid,&status,WUNTRACED);
}
return 0;
}	

//function that pipes
int piper(int num,char **parameters){
char *myargs[num+1];
for(int i = 0;i<num;++i)
	myargs[i] = parameters[i];
myargs[num] = NULL;
char *myargs2[num+1];
for(int i = num+1;i<num+2;++i)
	myargs2[i] = parameters[i];
myargs2[num+2] = NULL;
int p[2];
pipe(p);

pid = fork();
if(pid == 0){//child
	close(0);
	close(p[0]);
	close(p[1]);
	dup(p[0]);
	if((execvp(myargs2[0],myargs2))< 0)
		printf("Execution Error\n");
	exit(1);
}else if(pid < 0){
	printf("Fork Error\n");
}else{//parent
	close(1);
	close(p[0]);
	close(p[1]);
	dup(p[1]);
	if((execvp(myargs[0],myargs))<0)
		printf("Execution Error 2\n");
}
return 0;



}
