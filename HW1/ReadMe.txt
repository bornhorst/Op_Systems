READ_ME File

----------------------------------------------------------------
***header program***
----------------------------------------------------------------
(info)
-header takes either 1 or 2 arguments(filename and n)
-if no n is specified then n will be 1
-n is equal to the number of lines read from a file
-to run the program, the user would input "./header <filename n"
-the program will read 10 characters at a time from the file

(design)
-the design of this program was fairly straightforward
-to get it to work originally I had to make the buffer 1
-I was having problems reading the file 10 chars at time
because the write was writing some of the additional buffer
to the next line
-I decided to count the newlines and count the amount of times
read() was being executed
-this allowed me to conrol the output with write() 

(time)
-design: 1 hr, code: 2-3 hrs, documentation: 30 min

------------------------------------------------------------------
***timer program***
------------------------------------------------------------------
(info)
-timer takes an argument for a program name
-timer executes program name and calculates the elapsed time
-to run the program, the user would input "./timer ./program_name"

(design)
-it took some reading to find out that I needed to use a fork 
process to get this to work correctly
-used man pages to figure out how gettimeofday() works
-used lecture slides to figure out how to execute a file with
execlp() command

(time)
-design: 1-2 hours, code: 1 hour, documentation: 30 min

-------------------------------------------------------------------
***piper program***
-------------------------------------------------------------------
(info)
-to run piper, the user would input "./piper"
-the program uses fgets() to read user input from the console until
ctrl-d is pressed
-the parent process writes this input to the child and the child
removes any 'q' from the input and writes it back out to the console

(design)
-the problem I had with this program is getting it to write multiple 
lines 
-so far the program only works correctly if the user doesn't enter a 
new line into the console during input
-if this happens then only the last line is written to the console
-creating a fork process was very similar to the timer program 
except that this one communicates through a pipe with read and write

(time)
-design: 1-2 hours, code: 3-4 hours, documentation: 30 min

---------------------------------------------------------------------
***signaler program***
---------------------------------------------------------------------
(info)
-to run signaler, the user would input "./signaler"
-the program outputs "HELLO" every 2 seconds until 10 seconds have
passed
-program exits after 10 seconds and displays the amount of times
ctrl-c was pressed during the loop process

(design)
-read the unix book to learn how signals work with SIGINT
-this was the least difficult program to make
-the way I wrote the program, the interrupt actually speeds up 
program execution
-the program should take 10 seconds to run buf if the user types
ctrl-c multiple times it executes much faster because the 
interrupt causes it to skip over the sleep cycle

(time)
-design: 30 min, code: 30 min, documentation: 30 min

