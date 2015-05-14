/*=============================================================================
 |    File Name:  csce3613/homework3/assign3.c
 |
 |       Author:  Gage Alvis
 |     Language:  ANSI C (tested using gcc on turing )
 |   To Compile:  gcc -Wall assign3.c
 |
 |        Class:  CSCE3613
 |      Project:  homework assignment 3
 |   Assumption:  1 pipe, 1 redirect
 | Date Created:  3-08-2015
 |     Modified:  3-19-2015
 |
 +-----------------------------------------------------------------------------
 |
 |  Description: A c program implementing basic operation of a linux shell
 |					that handles command line user input and interactive user
 |					input; this program is an extension of assign1 and assign2;
 |					all command types are executed; Program forks processes when necessary
 |					and logs process id accordingly
 |
 |	  Input:  Command line user input from keyboard at runtime or user input
 |				after prompt
 |
 |	 Output:  Print statements identifying command, result, and execution of command
 |
 |    Algorithm:  Loop through command and dynamically alloc space for each argument
 |					and set flags when program detects identifiers (pipe, redirects)
 |
 |  Required Features Not Included:  The program adheres to all
 |		requirements stated in the program assignment, and all
 |		required features are included.
 |
 |   Known Bugs:  Program continues with bad input: multiple pipe flags or redirects
 |					will return parse result as if it is a correct input - does not
 |					hinder overall program design or desired outcome
 |
 +===========================================================================*/
 #include <stdio.h>
// needed for string library
#include <string.h>
// needed for memory allocation
#include <stdlib.h>
// used for wait, execvp, fork
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
// predefined array, buf sizes
#define CSTRSIZE 100
#define CMDSIZE 30
#define BUFSIZE 1024

#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h> 

/* global vars */
// shell prompt, quit string for strcmp					
const char* PROMPT = "myshell-%";
const char* QUIT = "quit";
// global flags for detecting command complexity
int GLOBAL_PIPE_FLAG;
int GLOBAL_REDR_OUT_FLAG;
int GLOBAL_REDR_OUTAPP_FLAG;
int GLOBAL_REDR_INP_FLAG;

/* function definitions */
int parse_command(char* line,
					char** cmd1,
					char** cmd2,
					char* infile,
					char* outfile);
int isCmd1();
int isCmd2();
int isRedr();
int parseFlagResult();
void resetGlobals();
void writeLog(int proc, char* action, char* function);

/* execute functions */
void exec_cmd(char** cmd1);
void exec_cmd_in(char** cmd1, char* infile);
void exec_cmd_opt_in_append(char** cmd1, char* infile, char* outfile);
void exec_cmd_opt_in_write(char** cmd1, char* infile, char* outfile);
void exec_pipe(char** cmd1, char** cmd2);
void exec_pipe_in(char** cmd1, char** cmd2, char* infile);
void exec_pipe_opt_in_append(char** cmd1, char** cmd2, char* infile, char* outfile);
void exec_pipe_opt_in_write(char** cmd1, char** cmd2, char* infile, char* outfile);


int main(int argc, char *argv[]){
	// init local vars
	int arg_index;
	int parse_result;
	char infile[CSTRSIZE];
	char outfile[CSTRSIZE];
	char* cmd1[CMDSIZE];
	char* cmd2[CMDSIZE];
	char user_input[BUFSIZE];
	// init globals
	resetGlobals();
	// declare temp values
	parse_result = 9;
	arg_index = 1;
	outfile[0] = 0;
	infile[0] = 0;
	user_input[0] = 0;
	// on 0 user quits
	while(parse_result > 0){
		printf("%s ",PROMPT);
		//check for command-lines
		if (arg_index < argc){
			strcpy(user_input, argv[arg_index]);
			printf("%s\n", user_input);
			arg_index++;
		} else {
			while (fgets(user_input, BUFSIZE, stdin) == NULL)
				printf("%s", PROMPT);
			// fgets adds \n to end of string - replace with NULL
			user_input[strnlen(user_input, BUFSIZE)-1] = '\0';
		}
		//skip if user presses enter or ctrl+d
		if (*user_input != '\0'){
			printf("\tuser command:\t%s\n", user_input);
			parse_result = parse_command(user_input, cmd1, cmd2, infile, outfile);
			printf("\tparse_command:\t%i\n", parse_result);
			//display outfile/infile if possible
			if(strlen(outfile) > 0)
				printf("\toutfile:\t%s\n", outfile);
			if(strlen(infile) > 0)
				printf("\tinfile:\t%s\n", infile);
			// execute simple commands only
			switch (parse_result){
				case 1:
					exec_cmd(cmd1);
					break;
				case 2:
					exec_cmd_in(cmd1, infile);
					break;
				case 3:
					exec_cmd_opt_in_append(cmd1, infile, outfile);
					break;
				case 4:
					exec_cmd_opt_in_write(cmd1, infile, outfile);
					break;
				case 5:
					exec_pipe(cmd1, cmd2);
					break;
				case 6:
					exec_pipe_in(cmd1, cmd2, infile);
					break;
				case 7:
					exec_pipe_opt_in_append(cmd1, cmd2, infile, outfile);
					break;
				case 8:
					exec_pipe_opt_in_write(cmd1, cmd2, infile, outfile);
					break;
				case 9:
					printf("Not handled at this time!\n");
					break;				
			}
			//reset values to eval next command
			resetGlobals();
			outfile[0] = 0;
			infile[0] = 0;
		}
	}
	printf("user successfully quits program\n");	
	return 0;
}

int parse_command(char* line, char** cmd1, char** cmd2, char* infile, char* outfile){
	// init counters and temp pointers
	int counter = 0;
	int cmd1_counter = 0;
	int cmd2_counter = 0;
	int local_redirect_flag = 0;
	char* token;
	char* first;
	char* last;
	int index;
	int len = strlen(line);
	if(strcmp(line, QUIT)==0)
		return 0;	
	first = line;
	last = line;
	// iterate over each char
	for(index = 0; index <= len; index++, last++){
		counter++;
		//if currect char is in( |\n<>) assume token is found
		if ((*last==' ')||(*last=='|')||(*last=='\0') || (*last=='<') || (*last=='>')){
			//alloc for token
			token = malloc(sizeof(char*) * (counter+1));
			int i = 0;
			//copy chars into token
			while((first[i] != *last) && (token[i] = first[i]))
				i++;
			token[i] = '\0';
			//printf("token test:\t%s\t%i\n", token, i);
			// make sure token is not empty or space
			if (!(*token=='\0' || *token==' ')){
				// check global flags to determine where token goes
				if (local_redirect_flag){
					//add to outfile or infilfe base on type
					// if multiple redirects occur, outfile/infile is overwritten
					if(GLOBAL_REDR_OUTAPP_FLAG || GLOBAL_REDR_OUT_FLAG){
						strcpy(outfile, token);
					}else {				
						strcpy(infile, token);
					}
					local_redirect_flag = 0;
				}
				else if(isCmd1()){
					//printf("cmd1\tcounter:\t%i\tcmd1_counter:\t%i\n", counter, cmd1_counter);
					// dynamic alloc space for new token
					cmd1[cmd1_counter] = malloc(sizeof(char*) * (counter+1));
					strcpy(cmd1[cmd1_counter], token);
					cmd1_counter++;
				} else if (isCmd2()){
					//printf("cmd2\tcounter:\t%i\tcmd2_counter:\t%i\n", counter, cmd2_counter);
					// dynamic alloc space for new token
					cmd2[cmd2_counter] = malloc(sizeof(char*) * (counter+1));
					strcpy(cmd2[cmd2_counter], token);
					cmd2_counter++;
				}
			}	
			// free space, reset local vars
			free(token);
			counter = 0;
			first = last+1;	
			// set pipe and redr flags if necessary
			if(*last=='|'){
				GLOBAL_PIPE_FLAG = 1;
			}
			else if(*last=='>'){
				local_redirect_flag = 1;
				if(*first=='>'){
					GLOBAL_REDR_OUTAPP_FLAG = 1;
					index++;
					last++;
					first++;
				}
				else
					GLOBAL_REDR_OUT_FLAG = 1;
			}
			else if(*last=='<'){
				local_redirect_flag = 1;
				GLOBAL_REDR_INP_FLAG = 1;
			}
		}
	}
	//end with NULL
	cmd1[cmd1_counter] = '\0';
	cmd2[cmd2_counter] = '\0';
	//separate function to determine command complexity
	return parseFlagResult();
}
// cmd1 until first pipe
int isCmd1(){
	return ( !GLOBAL_PIPE_FLAG);
}
// cmd2 after first pipe and before redirects
int isCmd2(){
	return ( GLOBAL_PIPE_FLAG);
}
// after any redirects
int isRedr(){
	return ( GLOBAL_REDR_OUT_FLAG ||
				GLOBAL_REDR_OUTAPP_FLAG ||
				GLOBAL_REDR_INP_FLAG);
}
// return 9 default
int parseFlagResult(){
	int result = 9;	
	if (!GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				!GLOBAL_REDR_INP_FLAG)
		result = 1;
	else if(!GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				GLOBAL_REDR_INP_FLAG)
		result = 2;
	else if(!GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				GLOBAL_REDR_OUTAPP_FLAG)
		result = 3;
	else if(!GLOBAL_PIPE_FLAG &&				
				GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG)
		result = 4;
	else if(GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				!GLOBAL_REDR_INP_FLAG)
		result = 5;
	else if(GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				GLOBAL_REDR_INP_FLAG)
		result = 6;
	else if(GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				GLOBAL_REDR_OUTAPP_FLAG)
		result = 7;
	else if(GLOBAL_PIPE_FLAG &&				
				GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG)
		result = 8;
				
	return result;
}
//reset global flags
void resetGlobals(){
	GLOBAL_PIPE_FLAG = 0;
	GLOBAL_REDR_OUT_FLAG = 0;
	GLOBAL_REDR_OUTAPP_FLAG = 0;
	GLOBAL_REDR_INP_FLAG = 0;
}
//execute simple command
void exec_cmd(char** cmd1){
	int pid;
	writeLog(-1, "before fork", "exec_cmd");
	if((pid=fork()) == 0){
		writeLog(pid, "after fork", "exec_cmd");
		execvp(cmd1[0], cmd1);
		writeLog(pid, "exec error", "exec_cmd");
	}
	else if(pid < 0)
		writeLog(pid, "could not fork process", "exec_cmd");
	else{
		writeLog(pid, "before wait", "exec_cmd");
		wait(NULL);
		writeLog(pid, "after wait", "exec_cmd");
	}
}
//execute simple command with input redir
void exec_cmd_in(char** cmd1, char* infile){
	int pid, fd_in;
	writeLog(-1, "before fork", "exec_cmd_in");
	if((pid=fork()) == 0){
		writeLog(pid, "after fork", "exec_cmd");
		//duplicate stdin file descriptor
		//int fd_in;
		fd_in = open(infile, O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		//execute cmd1
		execvp(cmd1[0], cmd1);
		writeLog(pid, "exec error", "exec_cmd_in");
	}
	else if(pid < 0)
		writeLog(pid, "could not fork process", "exec_cmd_in");
	else{
		writeLog(pid, "before wait", "exec_cmd_in");
		wait(NULL);
		writeLog(pid, "after wait", "exec_cmd_in");
	}
}
//execute simple command with output append redir possible input redir
void exec_cmd_opt_in_append(char** cmd1, char* infile, char* outfile){
	int pid, fd_in, fd_out;
	writeLog(-1, "before fork", "exec_cmd_opt_in_append");
	if((pid=fork()) == 0){
		writeLog(-1, "after fork", "exec_cmd_opt_in_append");
		//int fd_in, fd_out;
		//dup stdout descriptor
		fd_out = open(outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		//if infile then dup stdin descriptor
		if(strlen(infile)>0){			
			fd_in = open(infile, O_RDONLY);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		//execute		
		execvp(cmd1[0], cmd1);		
		writeLog(pid, "exec error", "exec_cmd_opt_in_append");
	}
	else if(pid < 0)
		writeLog(pid, "could not fork process", "exec_cmd_opt_in_append");
	else{
		writeLog(pid, "before wait", "exec_cmd_opt_in_append");
		wait(NULL);
		writeLog(pid, "after wait", "exec_cmd_opt_in_append");
	}
}
//execute simple command with output write redir possible input redir
void exec_cmd_opt_in_write(char** cmd1, char* infile, char* outfile){
	int pid;
	if((pid=fork()) == 0){
		int fd_in, fd_out;
		//dup stdout descriptor
		fd_out = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		//if infile then dup stdin descriptor
		if(strlen(infile)>0){			
			fd_in = open(infile, O_RDONLY);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		//execute		
		execvp(cmd1[0], cmd1);
	}
	else if(pid < 0)
		perror("\nError: could not start process\n");
	else
		wait(NULL);
}
//execute pipe with no redir
void exec_pipe(char** cmd1, char** cmd2){
    int fd_pipe[2]; // return value from the pipe system call
    int fd_out, fd_in;
	int pid1, pid2;
	pipe(fd_pipe);
	//fork process
	if((pid1=fork()) == 0){
		//child 1
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		execvp(cmd1[0], cmd1);
	}
	else if(pid1 < 0)
		perror("\nError: could not start process 1\n");
	else{	
		if((pid2=fork()) == 0){
			//child 2
			close(fd_pipe[1]);
			dup2(fd_pipe[0], STDIN_FILENO);
			close(fd_pipe[0]);
			execvp(cmd2[0], cmd2);
		}
		else if(pid2 < 0)
			perror("\nError: could not start process 2\n");
		else{	
			wait(NULL);
		}
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	wait(NULL);
}
//execute pipe with input reidr on first cmd
void exec_pipe_in(char** cmd1, char** cmd2, char* infile){
    int fd_pipe[2]; // return value from the pipe system call
	int pid1, pid2;
	int fd_in;
	pipe(fd_pipe);
	//fork process
	if((pid1=fork()) == 0){
		//child 1
		int fd_in;
		fd_in = open(infile, O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		execvp(cmd1[0], cmd1);
	}
	else if(pid1 < 0)
		perror("\nError: could not start process 1\n");
	else{	
		if((pid2=fork()) == 0){
			//child 2
			close(fd_pipe[1]);
			dup2(fd_pipe[0], STDIN_FILENO);
			close(fd_pipe[0]);
			execvp(cmd2[0], cmd2);
		}
		else if(pid2 < 0)
			perror("\nError: could not start process 2\n");
		else{	
			wait(NULL);
		}
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	wait(NULL);
}
//execute pipe with output append possible input redir
void exec_pipe_opt_in_append(char** cmd1, char** cmd2, char* infile, char* outfile){
    int fd_pipe[2]; // return value from the pipe system call
	int pid1, pid2, fd_in, fd_out;
	pipe(fd_pipe);
	//fork process
	if((pid1=fork()) == 0){
		//child 1
		if(strlen(infile)>0){
			fd_in = open(infile, O_RDONLY);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		} else {close(fd_pipe[0]);}
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		execvp(cmd1[0], cmd1);
	}
	else if(pid1 < 0)
		perror("\nError: could not start process 1\n");
	else{	
		if((pid2=fork()) == 0){
			//child 2
			dup2(fd_pipe[0], STDIN_FILENO);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			fd_out = open(outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			execvp(cmd2[0], cmd2);
		}
		else if(pid2 < 0)
			perror("\nError: could not start process 2\n");
		else{
			wait(NULL);
		}
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	wait(NULL);
}
//execute pipe with output write possible input redir
void exec_pipe_opt_in_write(char** cmd1, char** cmd2, char* infile, char* outfile){
    int fd_pipe[2]; // return value from the pipe system call
	int pid1, pid2, fd_in, fd_out;
	pipe(fd_pipe);
	//fork process
	if((pid1=fork()) == 0){
		//child 1
		if(strlen(infile)>0){
			fd_in = open(infile, O_RDONLY);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		} else {close(fd_pipe[0]);}
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		execvp(cmd1[0], cmd1);
	}
	else if(pid1 < 0)
		perror("\nError: could not start process 1\n");
	else{	
		if((pid2=fork()) == 0){
			//child 2
			dup2(fd_pipe[0], STDIN_FILENO);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			fd_out = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			execvp(cmd2[0], cmd2);
		}
		else if(pid2 < 0)
			perror("\nError: could not start process 2\n");
		else{
			wait(NULL);
		}
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	wait(NULL);
}
//write process id and action to log foo.txt
void writeLog(int proc, char* action, char* function){
	FILE *foo;
	foo = fopen("foo.txt", "w");
	fprintf(foo, "Process id:\t%i\tAction:\t%s\n", proc, action);
	fclose(foo);
}
