#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int n = 0;

void sigint()
{
	++n;//count number of interrupts
}

int main(void)
{

int count = 0;

signal(SIGINT,sigint);//generate interrupt signal

while(count < 5){//count for 10 seconds unless interrupted
sleep(2);
write(STDOUT_FILENO,"HELLO\n",7);

++count;
}
printf("You pressed ctrl-c %d times.\n",n);

exit(0);

}
